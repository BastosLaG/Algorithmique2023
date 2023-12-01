#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../headers/catalan.h"

const struct Catalan_Func Catalan =
{
	.coefficient_binomial = from_binomial_coefficient,
	.iterative = from_iteration,
	.recursive = from_naive_recursion,
	.tests = tests
};

unsigned long from_binomial_coefficient(const unsigned long N)
{
	return binomial_coefficient_from(N * 2, N) / (N + 1);
}
unsigned long binomial_coefficient_from(const unsigned long N, unsigned long k)
{
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


unsigned long from_iteration(const unsigned long N)
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

unsigned long from_naive_recursion(const unsigned long N)
{
	if (N <= 1)
		return 1;
	unsigned long sum = 0;
	for (unsigned long index = 0; index < N; index += 1)
		sum += from_naive_recursion(index) * from_naive_recursion(N - index - 1);
	return sum;
}


float execution_time(unsigned long (*function_p)(const unsigned long), const unsigned long N)
{
	long start = clock();
	function_p(N);
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
void execution_time_test(unsigned long (*function_p)(const unsigned long))
{
	float execut_time;
	float overall_execution_time = 0.f;
	for (unsigned char index = 0; index < 50; index += 1)
	{
		execut_time = execution_time(function_p, index);
		printf("%s ( %02hhu ) : \033[33m%f\033[39ms: %s\n", function_name(function_p), index, execut_time, execut_time <= 0.001f ? "🟩" : execut_time <= 0.01f ? "🟨" : execut_time <= 0.1f ? "🟧" : execut_time <= 1.0f ? "🟥" : "⬛");
		if (execut_time > 1.f)
		{
			printf("%s ( %hhu ) Supérieur à 1s -> arret du test.\n", function_name(function_p), index);
			return;
		}
		overall_execution_time += execut_time;
	}
	printf("overall_execution_time: \033[33m%f\033[39ms.\n", overall_execution_time);
}

void tests(unsigned long (*function_p)(const unsigned long))
{
	printf("\nExecution time test:\n");
	execution_time_test(function_p);
}

char *function_name(void *function_p)
{
	if (function_p == from_binomial_coefficient)
		return "Catalan.from_binomial_coefficient";
	else if (function_p == from_iteration)
		return "Catalan.from_iteration";
	else if (function_p == from_naive_recursion)
		return "Catalan.from_naive_recursion";
	else
		return "unknown_function";
}
