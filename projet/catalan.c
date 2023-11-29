#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

// Structure pour stocker les informations sur une combinaison de parenthèses
typedef struct {
    char *str;
    int left;
    int right; 
} Node;

unsigned long long int catalanNumber(int n);

void parenthesize(int n);
void generateParenthesesRec(char current[], int left, int right, int n);

void generateParenthesesIte(int n);


int main() {
    clock_t start_time, end_time;
    double rec_time, ite_time, rec_time_2, ite_time_2; 
    int wordLength, wordLength_2;
    wordLength = 3;
    wordLength_2 = 5;

    // Mesurer le temps pour la manière récursive
    printf("\nVersion récursive :\n");
    start_time = clock();
    parenthesize(wordLength);
    end_time = clock();
    rec_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Mesurer le temps pour la maniere itérative
    printf("\nVersion itérative :\n");
    start_time = clock();
    generateParenthesesIte(wordLength);
    end_time = clock();
    ite_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Mesurer le temps pour la manière récursive
    printf("\nVersion récursive 2:\n");
    start_time = clock();
    parenthesize(wordLength_2);
    end_time = clock();
    rec_time_2 = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Mesurer le temps pour la maniere itérative
    printf("\nVersion itérative 2:\n");
    start_time = clock();
    generateParenthesesIte(wordLength_2);
    end_time = clock();
    ite_time_2 = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Afficher les résultats
    printf("\nTaille du mot = %d || Nombre de catalan = %lld\n", wordLength, catalanNumber(wordLength));
    printf("Temps d'exécution de la manière récursive : %f secondes\n", rec_time);
    printf("Temps d'exécution de la maniere itérative : %f secondes\n", ite_time);
    
    printf("\nTaille du mot = %d || Nombre de catalan = %lld\n", wordLength_2, catalanNumber(wordLength_2));
    printf("Temps d'exécution de la manière récursive : %f secondes\n", rec_time_2);
    printf("Temps d'exécution de la maniere itérative : %f secondes\n", ite_time_2);
    return 0;
}

// Fonction pour calculer le nombre de Catalan
unsigned long long int catalanNumber(int n) {
    unsigned long long int catalan = 1;
    for (int i = 0; i < n; ++i) {
        catalan *= (2 * n - i);
        catalan /= (i + 1);
    }
    catalan /= (n + 1);
    return catalan;
}

void generateParenthesesIte(int n) {
    int maxQueueSize = catalanNumber(n);
    Node *queue = (Node *)malloc(maxQueueSize * sizeof(Node));
    assert(queue);
    int debut = 0, fin = 0;

    queue[fin].str = (char *)malloc(2 * n + 1);
    assert(queue[fin].str);
    queue[fin].str[2 * n] = '\0';
    queue[fin].left = 0;
    queue[fin].right = 0;
    fin++;

    while (debut < fin) {
        char *current = queue[debut].str;
        int left = queue[debut].left;
        int right = queue[debut].right;
        debut++;

        if (left + right == 2 * n) {
            printf("%s\n", current);
        }

        if (left < n) {
            queue[fin].str = (char *)malloc(2 * n + 1);
            sprintf(queue[fin].str, "%s(", current);
            queue[fin].left = left + 1;
            queue[fin].right = right;
            fin++;
        }

        if (right < left) {
            queue[fin].str = (char *)malloc(2 * n + 1);
            sprintf(queue[fin].str, "%s)", current);
            queue[fin].left = left;
            queue[fin].right = right + 1;
            fin++;
        }
    }

}

void generateParenthesesRec(char current[], int left, int right, int n) {
    if (left + right == 2 * n) {
        printf("%s\n", current);
        return;
    }
    if (left < n) {
        current[left + right] = '(';
        generateParenthesesRec(current, left + 1, right, n);
    }
    if (right < left) {
        current[left + right] = ')';
        generateParenthesesRec(current, left, right + 1, n);
    }
}
void parenthesize(int n) {
    char current[2 * n + 1];  // +1 for the null terminator
    current[2 * n] = '\0';    // null terminator
    generateParenthesesRec(current, 0, 0, n);
}