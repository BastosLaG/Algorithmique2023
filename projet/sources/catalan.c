#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "../headers/catalan.h"

const struct Catalan_Func Catalan = {
	.recursive = recursive,
	.iterative = iterative,
	.generative = generative,
	.factoriel = factoriel,
	.combinatoire_interpreter = combinatoire_interpreter,
	.hypergeometric = hypergeometric,
	.infini = infini,
	.integral = integral,
	.tests = c_tests
};

// recursion
unsigned long long int recursive(int N) {
	if (N <= 1)
		return 1;
	unsigned long long int somme = 0;
	int index;
	for (index = 0; index < N; index += 1)
		somme += recursive(index) * recursive(N - index - 1);
	return somme;
}
unsigned long long int iterative(int n) {
    unsigned long long int *nombresCatalan = malloc((sizeof *nombresCatalan) * (n + 1));
	unsigned long long int resultat;
	int indexcourant, indexPP; 
    nombresCatalan[0] = nombresCatalan[1] = 1;
    for (indexcourant = 2; indexcourant <= n; indexcourant += 1) {
        nombresCatalan[indexcourant] = 0;
        for (indexPP = 0; indexPP < indexcourant; indexPP += 1) {
            nombresCatalan[indexcourant] += nombresCatalan[indexPP] * nombresCatalan[indexcourant - indexPP - 1];
        }
    }
    resultat = nombresCatalan[n];
    free(nombresCatalan);
    return resultat;
}

// Explicite
unsigned long long int factoriel(int N) {
	if (N < 0) return 0;
    if (N == 0) return 1;
    return (unsigned long long int)(factoriel_calcule(2 * N) / ((double)factoriel_calcule(N + 1) * factoriel_calcule(N)));
}
unsigned long long int factoriel_calcule(int N) {
	if (N <= 1) return 1;
	else return (unsigned long long int)N * factoriel_calcule(N - 1);
}
unsigned long long int combinatoire_interpreter(int N) {
    unsigned long long int result = 1;
	int i;
    for (i = 0; i < N; ++i) {
        result *= (2 * N - i);
        result /= (i + 1);
    }
    return result / (N + 1);
}

// Generative
unsigned long long int generative(int N) {
    unsigned long long int result = 1;
	int i; 
    for (i = 1; i <= N; ++i) {
        result *= (1 - sqrt(1 - 4.0 / (i * i)));
    }
    return result / 2.0;
}

// Coef Binomial utile pour la suite
unsigned long long int coef_bin(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    } else {
        return coef_bin(n - 1, k - 1) * n / k;
    }
}
// Expression intégrale
unsigned long long int integral(int n) {
    float result = 1.0;
    for (int k = 1; k <= n; ++k) {
        result *= (2.0 * k - 1) / (n + k);
    }
    return (unsigned long long int) result;
}

// Hypergeometric
unsigned long long int hypergeometric(int n) {
    return coef_bin(2 * n, n) / (n + 1);
}

// Série infinie
unsigned long long int infini(int n) {
    unsigned long long int result = 0;
    int k;
    for (k = 0; k <= n; k++) {
        result += coef_bin(n, k) * coef_bin(n, k) / (k + 1);
    }
    return result;
}


// Zone pour les tests
float c_execution_time(unsigned long long int (*function_p)(int), int N) {
	long start = clock();
	function_p(N);
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
void c_execution_time_test(unsigned long long int (*function_p)(int)) {
	float execut_time;
	float overall_execution_time = 0.f;
	float arret_time = 0.5f;
	float arret_time_s = 60.0f;
 	float index;
	float max_index = 100000;
	float percent;
	for (index = 0; index <= max_index; index += 1) {
		execut_time = c_execution_time(function_p, index);
		if (execut_time > arret_time) {
			
			printf("index_execution_time ( \033[1;31m%0.f\033[0m ) : \033[33m%f\033[39ms > \033[33m%.2f\033[39ms -> arret du test.\n", index-1, execut_time, arret_time);
			percent = ((index-1)/max_index)*100;
			printf("%s | 0 -> \033[1;31m%0.f\033[0m ( \033[1;31m%.3f%%\033[0m ) | overall_execution_time: \033[33m%f\033[39ms.\n",c_function_name(function_p), index-1, percent, overall_execution_time);
			return;
		}
		overall_execution_time += execut_time;
		if (overall_execution_time >= arret_time_s)
		{
			printf("overall_execution_time ( \033[1;31m%0.f\033[0m ): \033[33m%f\033[39ms > \033[33m%.0f\033[39ms -> arret du test.\n", index-1, overall_execution_time, arret_time_s);
			percent = ((index-1)/max_index)*100;
			printf("%s | 0 -> \033[1;31m%0.f\033[0m ( \033[1;31m%.3f%%\033[0m )  | overall_execution_time: \033[33m%f\033[39ms.\n", c_function_name(function_p), index-1, percent, overall_execution_time);
			return;
		}
	}
	percent = ((index-1)/max_index)*100;
	printf("%s | 0 -> \033[1;32m%0.f\033[0m ( \033[1;32m%.3f%%\033[0m )  | overall_execution_time: \033[33m%f\033[39ms.\n",c_function_name(function_p), index-1, percent, overall_execution_time);
}

void c_tests(unsigned long long int (*function_p)(int)) {
	printf("\nExecution time test %s:\n", c_function_name(function_p));
	c_execution_time_test(function_p);
}

char *c_function_name(void *function_p) {
	if (function_p == combinatoire_interpreter)
		return "Catalan -> combinatoire_interpreter";
	else if (function_p == iterative)
		return "Catalan -> iterative";
	else if (function_p == recursive)
		return "Catalan -> recursive";
	else if (function_p == generative)
		return "Catalan -> generative";
	else if (function_p == factoriel)
		return "Catalan -> factoriel";
	else if (function_p == hypergeometric)
		return "Catalan -> hypergeometric";
	else if (function_p == infini)
		return "Catalan -> infini";
	else if (function_p == integral)
		return "Catalan -> integral";
	else
		return "unknown_function";
}
