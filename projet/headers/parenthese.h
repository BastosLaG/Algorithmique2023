#ifndef PARENTHESE_H
#define PARENTHESE_H
    
    struct Parenthese_Func {
        void (*recursive)(int);   
        // void (*iterative)(int);
        void (*tests)(void (*)(int));
    };
    extern const struct Parenthese_Func Parenthese;

    // struct Parenthese_struct;
    // typedef struct Parenthese_struct{
    //     char *str;
    //     int left;
    //     int right; 
    // }Parenthese_struct;
    
    // extern Parenthese_struct *queue;

    
    void parenthese_rec(int);
    void generateParenthesesRec(char [], int, int, int );
    // void generateParenthesesIte(int);

    float p_execution_time(void (*function_p)(int), int N);
	void p_execution_time_test(void (*function_p)(int));
	void p_tests(void (*function_p)(int));
	char *p_function_name(void *function_p);

#endif
