#ifndef CATALAN_H
#define CATALAN_H

	struct Catalan_Func
	{
		unsigned long (*coefficient_binomial)(const unsigned long);	
		unsigned long (*iterative)(const unsigned long);
		unsigned long (*recursive)(const unsigned long);
		void (*tests)(unsigned long (*)(const unsigned long));
	};
	extern const struct Catalan_Func Catalan;

	unsigned long binomial_coefficient(const unsigned long N);
	unsigned long binomial_coefficient_calcul(const unsigned long N, unsigned long k);
	unsigned long iterative(const unsigned long N);
	unsigned long recursive(const unsigned long N);
	
	float c_execution_time(unsigned long (*function_p)(const unsigned long), const unsigned long N);
	void c_execution_time_test(unsigned long (*function_p)(const unsigned long));
	void c_tests(unsigned long (*function_p)(const unsigned long));
	char *c_function_name(void *function_p);

#endif