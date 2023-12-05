#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../headers/catalan.h"

const struct Catalan_Func Catalan = {
	.recursive = recursive,
	.iterative = iterative,
	.coefficient_binomial = binomial_coefficient,
	.tests = c_tests
};

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

unsigned long long int binomial_coefficient(int N) {
	return binomial_coefficient_calcul(N * 2, N) / (N + 1);
}
unsigned long long int binomial_coefficient_calcul(int N, int k) {
	unsigned long long int result = 1;
	int temp, index;
	temp = N - k;
	if (k > temp) k = temp;
	for (index = 0; index < k; index += 1)
	{
		result *= (N - index);
		result /= (index + 1);
	}
	return result;
}

float c_execution_time(unsigned long long int (*function_p)(int), int N) {
	long start = clock();
	function_p(N);
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
void c_execution_time_test(unsigned long long int (*function_p)(int)) {
	float execut_time;
	float overall_execution_time = 0.f;
	float arret_time = 0.5f;
	unsigned long long int index;
	for (index = 0; index <= 1000; index += 1) {
		execut_time = c_execution_time(function_p, index);
		if (execut_time > arret_time) {
			printf("( %llu ) : \033[33m%f\033[39m supérieur à \033[33m%f\033[39ms -> arret du test.\n", index, execut_time, arret_time);
			printf("%s | overall_execution_time: \033[33m%f\033[39ms.\n",c_function_name(function_p),  overall_execution_time);
			return;
		}
		overall_execution_time += execut_time;
	}
	printf("%s | overall_execution_time: \033[33m%f\033[39ms.\n",c_function_name(function_p),  overall_execution_time);
}

void c_tests(unsigned long long int (*function_p)(int)) {
	printf("\nExecution time test:\n");
	c_execution_time_test(function_p);
}

char *c_function_name(void *function_p) {
	if (function_p == binomial_coefficient)
		return "Catalan -> binomial_coefficient";
	else if (function_p == iterative)
		return "Catalan -> iterative";
	else if (function_p == recursive)
		return "Catalan -> recursive";
	else
		return "unknown_function";
}
