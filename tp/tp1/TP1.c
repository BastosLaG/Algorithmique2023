#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#define ITER 100
#define MAX 10

typedef unsigned long long int ullint;
struct paire {
  ullint fun;
  ullint fdeux;
};
typedef struct paire paire;

int mult (int a, int b);
int multrt (int a, int b, int acc);
int multi (int a, int b);
int qmul (int a, int b);

int puissance(int a, int b);
int puissanceR(float a, int b);
int puissanceRT(int a, int b, int acc);
int puissanceQ(int a, int b);

ullint fibonacciR(int n);
ullint fibonacci(int n);
ullint fibonacciRT(int n, int a, int b);
ullint fibonacciLog(int n);

paire fiblog (int n);
ullint fibo (int n);

void printPascalTriangle(int n);
int coeffBinomialR(int n, int m);
int coeffBinomialItab(int n, int m);
int coeffBinomialIvec(int n, int m);
// rajouter Itérative incrémentale
int factorial(int n);
int coeffBinomialfact(int n, int k);

int main () {
	int test1 = 1;
    int test2 = 1;
    int test3 = 1;

    clock_t start_t, end_t;
    double total_t;

    if (test1){
        int n, i, j;
        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = puissance(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\npuissance : \n"); //O -> b
        printf("Delta temps : %f\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = puissanceR(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\npuissance récursif : \n"); //O -> b
        printf("Delta temps : %f\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = puissanceQ(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\nPuissance binaire : \n"); //O -> log b
        printf("Delta temps : %f\n\n", total_t  );
    }

    if (test2){
        int n, i, j;
        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = fibonacciR(j);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\nFibonnacci récursif : \n"); //O -> 2^n
        printf("Delta temps : %f\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = fibonacci(j);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\nFibonnacci récursif terminal : \n"); //O -> 2^n
        printf("Delta temps : %f\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = 1; j < MAX; j++) n = fibonacciLog(j);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("\nFibonnacci logaritmique : \n"); //O -> log n
        printf("Delta temps : %f\n\n", total_t  );
    }

    if (test3){
		int n, i, j;

        start_t = clock();
        printPascalTriangle(10);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Delta temps : %f\n\n", total_t  );
		
        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = i+1; j < MAX; j++) n = coeffBinomialR(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Coeff binomial récursive : \n"); //O -> 2*n
        printf("Delta temps : %f\n\n", total_t  );
		
        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = i+1; j < MAX; j++) n = coeffBinomialItab(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Coeff binomial itératif tableau : \n"); 
        printf("Delta temps : %f\n\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = i+1; j < MAX; j++) n = coeffBinomialIvec(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		printf("Coeff binomial itératif vecteur : \n"); 
        printf("Delta temps : %f\n\n", total_t  );

        start_t = clock();
        for (i = 1; i < ITER; i++){
            for (j = i+1; j < MAX; j++) n = coeffBinomialfact(j, i);
        }
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		printf("Coeff binomial factorielle : \n"); 
        printf("Delta temps : %f\n\n", total_t  );

    }
    return 0;
}



// Multiplication 
int mult (int a, int b){
    if (b != 0)
        return a + mult(a, b-1);
    return 0;
}
int multrt (int a, int b, int acc){
    if (b == 0)
        return acc;
    return multrt (a, b - 1, acc + a);
}
int multi (int a, int b){
    if (b < 0)
        return - multrt(a, -b, 0);
    return  multrt(a, b, 0);
}
int qmul (int a, int b){
    int res;
    res = 0;
    while (b) {
        if (b & 0x01)
        res += a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

//Puissance 
int puissance(int a, int b){
  if (b > 0)
    return a * puissance(a, b-1);
  return 1;
}

int puissanceRT(int a, int b, int acc){
    if(b==0){
        return acc;
    }
    return puissanceRT(a, b-1, acc * a);
    
}
int puissanceR(float a, int b){
    return puissanceRT(a, b, 1);
}

int puissanceQ(int a, int b){
    int res = 1;
    while (b) {
        if (b % 2 == 1) {
            res *= a;
        }
        a *= a;
        b /= 2;
    }
    return res;
}

//Fibonnacci 

ullint fibonacciR(int n){
    if(n == 0){
        return 0;
    }else if (n == 1){
        return 1;
    }
    return fibonacciR(n-1) + fibonacciR(n-2);
}

ullint fibonacciRT(int n, int a, int b){
    if (n > 2) {
        return fibonacciRT(n - 1, b, a + b);
    } else {
        return a + b;
    }
}
ullint fibonacci(int n){
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }else{
        return fibonacciRT(n, 0, 1);
    }
}

ullint fibonacciLog(int n){
    if(n==0){
        return 0;
    }
    ullint F[2][2] =  {{1,1},{1,0}};
    ullint result[2][2] = {{1, 0}, {0, 1}};

    while (n > 0) {
        if (n % 2 == 1) {
            ullint x = result[0][0] * F[0][0] + result[0][1] * F[1][0];
            ullint y = result[0][0] * F[0][1] + result[0][1] * F[1][1];
            ullint z = result[1][0] * F[0][0] + result[1][1] * F[1][0];
            ullint w = result[1][0] * F[0][1] + result[1][1] * F[1][1];

            result[0][0] = x;
            result[0][1] = y;
            result[1][0] = z;
            result[1][1] = w;
        }
        ullint x = F[0][0] * F[0][0] + F[0][1] * F[1][0];
        ullint y = F[0][0] * F[0][1] + F[0][1] * F[1][1];
        ullint z = F[1][0] * F[0][0] + F[1][1] * F[1][0];
        ullint w = F[1][0] * F[0][1] + F[1][1] * F[1][1];

        F[0][0] = x;
        F[0][1] = y;
        F[1][0] = z;
        F[1][1] = w;
        n /= 2;
    }

    return result[0][1];
}

paire fiblog (int n){
  paire mi, res;
  int i;

  if (n < 2) {
	res.fun = (ullint) 1;
	res.fdeux = (ullint) 1;
	return res;
  }
  i = n >> 1;
  mi = fiblog(i);
  if (n & 0x01) {
	res.fdeux = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
	res.fun = (mi.fun + mi.fdeux + mi.fdeux) * mi.fun;
	return res;
  }
  res.fun = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
  res.fdeux = (mi.fun + mi.fun - mi.fdeux) * mi.fdeux;
	/* car on cherche fib(n+1) */
  return res;
}
ullint fibo (int n){
  paire res;
  if (n >= 0 && n < 92) {
	res = fiblog (n);
	return res.fun;
  }
  return (ullint) 0;
}

// Binaume de Newton / triangle de Pascale

void printPascalTriangle(int n){
    for (int line = 0; line < n; line++) {
        for (int k = 0; k <= line; k++) {
            printf("%d ", coeffBinomialR(line, k));
        }
        printf("\n");
    }
}

int coeffBinomialR(int n, int m){
    if (m == 0 || m == n) {
        return 1;
    }
    return coeffBinomialR(n - 1, m - 1) + coeffBinomialR(n - 1, m);
}

int coeffBinomialItab(int n, int m){
	int ** t0 = malloc(m* sizeof(int*));
	for(int i = 0; i <= n; ++i){
		int * t1 = malloc(n * sizeof(int));
		t0[i] = t1;
		for( int j = 0; j < i; ++j)
			t1[j] = t0[i-1][j] + t0[i-1][j-1];
		t0[i][i] = 1;
	}
   return t0[n][m] ;
}

int coeffBinomialIvec(int n, int m){
    int temp, prev;
    int coeff[n + 1];
    coeff[0] = 1;
    for (int i = 1; i <= n; i++) {
        prev = 1;
        for (int j = 1; j < i; j++) {
            temp = coeff[j];
            coeff[j] += prev;
            prev = temp;
        }
        coeff[i] = 1;
    }
    return coeff[n-m];
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}
int coeffBinomialfact(int n, int m) {
    return factorial(n) / (factorial(m) * factorial(n - m));
}
