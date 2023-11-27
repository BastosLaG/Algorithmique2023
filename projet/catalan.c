#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Structure pour stocker les informations sur une combinaison de parenthèses
typedef struct {
    char *str;
    int left;
    int right; 
} InfoParentheses;

unsigned long long int calculateCatalan(int n);

void parenthesize(int n);
void generateParenthesesRec(char current[], int left, int right, int n);

void generateParenthesesIte(int n);


int main() {
    clock_t start_time, end_time;
    double rec_time, ite_time, rec_time_2, ite_time_2; 
    int wordLength = 3, wordLength_2 = 5;

    // // Mesurer le temps pour la manière récursive
    // printf("Version récursive :\n");
    // start_time = clock();
    // parenthesize(wordLength);
    // end_time = clock();
    // rec_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Mesurer le temps pour la maniere itérative
    printf("\nVersion itérative :\n");
    start_time = clock();
    generateParenthesesIte(wordLength);
    end_time = clock();
    ite_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    parenthesize(wordLength);

    // // Mesurer le temps pour la manière récursive
    // printf("Version récursive 2:\n");
    // start_time = clock();
    // parenthesize(wordLength_2);
    // end_time = clock();
    // rec_time_2 = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Mesurer le temps pour la maniere itérative
    printf("\nVersion itérative 2:\n");
    start_time = clock();
    generateParenthesesIte(wordLength_2);
    end_time = clock();
    ite_time_2 = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    parenthesize(wordLength);

    // Afficher les résultats
    printf("\nTaille du mot = %d || Nombre de catalan = %lld\n", wordLength, calculateCatalan(wordLength));
    printf("Temps d'exécution de la manière récursive : %f secondes\n", rec_time);
    printf("Temps d'exécution de la maniere itérative : %f secondes\n", ite_time);
    
    printf("\nTaille du mot = %d || Nombre de catalan = %lld\n", wordLength_2, calculateCatalan(wordLength_2));
    printf("Temps d'exécution de la manière récursive : %f secondes\n", rec_time_2);
    printf("Temps d'exécution de la maniere itérative : %f secondes\n", ite_time_2);
    return 0;
}

// Fonction pour calculer le nombre de Catalan
unsigned long long int calculateCatalan(int n) {
    unsigned long long int catalan = 1;

    for (int i = 0; i < n; ++i) {
        catalan *= (2 * n - i);
        catalan /= (i + 1);
    }
    catalan /= (n + 1);

    return catalan;
}

void generateParenthesesIte(int n) {
    InfoParentheses file[calculateCatalan(n)];
    int debut = 0, fin = 0;

    // Initialisation avec la première combinaison vide
    file[fin].str = "";
    file[fin].left = 0;
    file[fin].right = 0;
    fin++;

    // Boucle principale pour générer les combinaisons
    while (debut < fin) {
        InfoParentheses courant = file[debut];
        debut++;

        // Si la longueur de la chaîne atteint 2n, affiche la combinaison
        if (courant.left + courant.right == 2 * n) {
            printf("%s\n", courant.str);
        } else {
            // Sinon, ajoute une parenthèse ouvrante si possible
            if (courant.left < n) {
                file[fin].str = strcat(strdup(courant.str), "(");
                file[fin].left = courant.left + 1;
                file[fin].right = courant.right;
                fin++;
            }

            // Ajoute une parenthèse fermante si possible
            if (courant.right < courant.left) {
                file[fin].str = strcat(strdup(courant.str), ")");
                file[fin].left = courant.left;
                file[fin].right = courant.right + 1;
                fin++;
            }
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