#ifndef CATALAN_H
#define CATALAN_H

	struct Catalan_Func
	{
		unsigned long long int (*recursive)(int);
		unsigned long long int (*iterative)(int);
		unsigned long long int (*factoriel)(int);
		unsigned long long int (*generative)(int);
		unsigned long long int (*combinatoire_interpreter)(int);	
		unsigned long long int (*hypergeometric)(int);
		unsigned long long int (*infini)(int);
		unsigned long long int (*integral)(int);
		void (*tests)(unsigned long long int (*)(int));
	};
	extern const struct Catalan_Func Catalan;

	unsigned long long int recursive(int N);
	unsigned long long int iterative(int N);
	unsigned long long int factoriel(int N);
	unsigned long long int factoriel_calcule(int N);
	unsigned long long int combinatoire_interpreter(int N);
    unsigned long long int generative(int N);
	unsigned long long int coef_bin(int n, int k);
	unsigned long long int hypergeometric(int n); 
	unsigned long long int infini(int n);
	unsigned long long int integral(int n);

	float c_execution_time(unsigned long long int (*function_p)(int), int);
	void c_execution_time_test(unsigned long long int (*function_p)(int));
	void c_tests(unsigned long long int (*function_p)(int));
	char *c_function_name(void *function_p);

#endif