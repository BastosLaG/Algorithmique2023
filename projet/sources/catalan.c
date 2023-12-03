#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../headers/catalan.h"

const struct Catalan_Func Catalan =
{
	.coefficient_binomial = binomial_coefficient,
	.iterative = iterative,
	.recursive = recursive,
	.tests = c_tests
};

unsigned long binomial_coefficient(const unsigned long N) {
	return binomial_coefficient_calcul(N * 2, N) / (N + 1);
}
unsigned long binomial_coefficient_calcul(const unsigned long N, unsigned long k) {
	unsigned long result = 1;
	{
		const unsigned long temp = N - k;
		if (k > temp) k = temp;
	}
	for (unsigned long index = 0; index < k; index += 1)
	{
		result *= (N - index);
		result /= (index + 1);
	}
	return result;
}


unsigned long iterative(const unsigned long N)
{
	unsigned long *const restrict CATALAN_NUMBERS = malloc((sizeof *CATALAN_NUMBERS) * (N + 1));
	CATALAN_NUMBERS[1] = CATALAN_NUMBERS[0] = 1;
	for (unsigned long long first_index = 2; first_index <= N; first_index += 1)
	{
		CATALAN_NUMBERS[first_index] = 0;
		for (unsigned long long second_index = 0; second_index < first_index; second_index += 1)
			CATALAN_NUMBERS[first_index] += CATALAN_NUMBERS[second_index] * CATALAN_NUMBERS[first_index - second_index - 1];
	} 
	const unsigned long CATALAN_NUMBER = CATALAN_NUMBERS[N];
	free(CATALAN_NUMBERS);
	return CATALAN_NUMBER;
}

unsigned long recursive(const unsigned long N)
{
	if (N <= 1)
		return 1;
	unsigned long sum = 0;
	for (unsigned long index = 0; index < N; index += 1)
		sum += recursive(index) * recursive(N - index - 1);
	return sum;
}


float c_execution_time(unsigned long (*function_p)(const unsigned long), const unsigned long N)
{
	long start = clock();
	function_p(N);
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
void c_execution_time_test(unsigned long (*function_p)(const unsigned long))
{
	float execut_time;
	float overall_execution_time = 0.f;
	for (unsigned char index = 0; index < 50; index += 1)
	{
		execut_time = c_execution_time(function_p, index);
		printf("%s ( %02hhu ) : \033[33m%f\033[39ms\n", c_function_name(function_p), index, execut_time);
		if (execut_time > 1.f)
		{
			printf("( %hhu ) : \033[33mSupérieur à 1s -> arret du test.\033[39m\n", index);
			return;
		}
		overall_execution_time += execut_time;
	}
	printf("overall_execution_time: \033[33m%f\033[39ms.\n", overall_execution_time);
}

void c_tests(unsigned long (*function_p)(const unsigned long))
{
	printf("\nExecution time test:\n");
	c_execution_time_test(function_p);
}

char *c_function_name(void *function_p)
{
	if (function_p == binomial_coefficient)
		return "Catalan.binomial_coefficient";
	else if (function_p == iterative)
		return "Catalan.iterative";
	else if (function_p == recursive)
		return "Catalan.recursive";
	else
		return "unknown_function";
}
