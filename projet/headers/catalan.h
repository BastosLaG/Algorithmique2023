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

	unsigned long from_binomial_coefficient(const unsigned long N);
	unsigned long binomial_coefficient_from(const unsigned long N, unsigned long k);
	unsigned long from_iteration(const unsigned long N);
	unsigned long from_naive_recursion(const unsigned long N);
	
	float execution_time(unsigned long (*function_p)(const unsigned long), const unsigned long N);
	void execution_time_test(unsigned long (*function_p)(const unsigned long));
	void tests(unsigned long (*function_p)(const unsigned long));
	char *function_name(void *function_p);

#endif