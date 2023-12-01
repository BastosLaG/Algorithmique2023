#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "headers/catalan.h"
#include "headers/parenthese.h"

int main() {
    Catalan.tests(Catalan.recursive);
	printf("\n");
	Catalan.tests(Catalan.iterative);
	printf("\n");
	Catalan.tests(Catalan.coefficient_binomial);
	printf("\n");
    Parenthese.tests(Parenthese.recursive);

    return 0;
}
