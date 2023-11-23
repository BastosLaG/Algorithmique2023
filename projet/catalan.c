#include <stdio.h>

void generateParentheses(char current[], int left, int right, int n) {
    if (left + right == 2 * n) {
        printf("%s\n", current);
        return;
    }

    if (left < n) {
        current[left + right] = '(';
        generateParentheses(current, left + 1, right, n);
    }
    if (right < left) {
        current[left + right] = ')';
        generateParentheses(current, left, right + 1, n);
    }
}

void parenthesize(int n) {
    char current[2 * n + 1];  // +1 for the null terminator
    current[2 * n] = '\0';    // null terminator

    generateParentheses(current, 0, 0, n);
}

int main() {
    int wordLength = 10;
    parenthesize(wordLength);

    return 0;
}
