#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "headers/catalan.h"
#include "headers/parenthese.h"

int main() {
    Parenthese.tests(Parenthese.recursive);
	printf("\n");
    Catalan.tests(Catalan.recursive);
	printf("\n");
	Catalan.tests(Catalan.iterative);
	printf("\n");
	Catalan.tests(Catalan.generative);
	printf("\n");
	Catalan.tests(Catalan.coefficient_binomial);
    return 0;
}
