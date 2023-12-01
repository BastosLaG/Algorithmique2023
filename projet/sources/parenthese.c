#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../headers/parenthese.h"

struct Parenthese_struct;
struct Parenthese_Func;

const struct Parenthese_Func Parenthese =
{
    .recursive = parenthese_rec,
    .iterative = generateParenthesesIte,
    .tests = test
};

float test(void (*function_p)(int), int n) {
    clock_t start = clock();
    function_p(n);
    return (float)(clock() - start) / CLOCKS_PER_SEC;
}

void generateParenthesesIte(const int N) {
    Parenthese_struct *queue = (Parenthese_struct *)malloc(N * sizeof(Parenthese_S));
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
