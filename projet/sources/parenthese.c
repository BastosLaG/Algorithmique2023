#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../headers/parenthese.h"

const struct Parenthese_Func Parenthese =
{
    .recursive = parenthese_rec,
    .iterative = generateParenthesesIte,
    .tests = p_tests
};

void generateParenthesesIte(const int N) {
    Parenthese_struct *queue = (Parenthese_struct *)malloc(N * sizeof(Parenthese_struct));
    assert(queue);
    int debut = 0, fin = 0;

    queue[fin].str = (char *)malloc(2 * N + 1);
    assert(queue[fin].str);
    queue[fin].str[2 * N] = '\0';
    queue[fin].left = 0;
    queue[fin].right = 0;
    fin++;

    while (debut < fin) {
        char *current = queue[debut].str;
        int left = queue[debut].left;
        int right = queue[debut].right;
        debut++;

        if (left + right == 2 * N) {
            printf("%s\n", current);
        }

        if (left < N) {
            queue[fin].str = (char *)malloc(2 * N + 1);
            sprintf(queue[fin].str, "%s(", current);
            queue[fin].left = left + 1;
            queue[fin].right = right;
            fin++;
        }

        if (right < left) {
            queue[fin].str = (char *)malloc(2 * N + 1);
            sprintf(queue[fin].str, "%s)", current);
            queue[fin].left = left;
            queue[fin].right = right + 1;
            fin++;
        }
    }
    // Libération de la mémoire allouée
    for (int i = 0; i < fin; i++) {
        free(queue[i].str);
    }
    free(queue);
}

void generateParenthesesRec(char current[], int left, int right, const int N) {
    if (left + right == 2 * N) {
        printf("%s\n", current);
        return;
    }
    if (left < N) {
        current[left + right] = '(';
        generateParenthesesRec(current, left + 1, right, N);
    }
    if (right < left) {
        current[left + right] = ')';
        generateParenthesesRec(current, left, right + 1, N);
    }
}
void parenthese_rec(const int N) {
    char current[2 * N + 1];  // +1 for the null terminator
    current[2 * N] = '\0';    // null terminator
    generateParenthesesRec(current, 0, 0, N);
}

float p_execution_time(void(*function_p)(int), int N)
{
	long start = clock();
	function_p(N);
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
void p_execution_time_test(void(*function_p)(int))
{
	float execut_time;
	float overall_execution_time = 0.f;
	for (unsigned char index = 1; index <= 50; index += 1)
	{
		execut_time = p_execution_time(function_p, index);
		printf("%s ( %02hhu ) : \033[33m%f\033[39ms\n\n", p_function_name(function_p), index, execut_time);
		if (execut_time > 1.f)
		{
			printf("( %hhu ) : \033[33mSupérieur à 1s -> arret du test.\033[39m\n\n", index);
			return;
		}
		overall_execution_time += execut_time;
	}
	printf("overall_execution_time: \033[33m%f\033[39ms.\n", overall_execution_time);
}

void p_tests(void(*function_p)(int))
{
	printf("\nExecution time test:\n");
	p_execution_time_test(function_p);
}

char *p_function_name(void *function_p)
{
	if (function_p == parenthese_rec)
		return "Parenthese.recursive";
	else if (function_p == generateParenthesesIte)
		return "Parenthese.iterative";
	else
		return "unknown_function";
}