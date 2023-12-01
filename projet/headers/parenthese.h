#ifndef PARENTHESE_H
#define PARENTHESE_H

    typedef struct Parenthese_struct{
        char *str;
        int left;
        int right; 
    }Parenthese_struct;
    typedef struct Parenthese_Func {
        void (*recursive)(int);   
        void (*iterative)(int);
        float (*tests)(void (*)(int));
    }Parenthese_Func;

    extern const struct Parenthese_struct Parenthese_S;
    extern const struct Parenthese_Func Parenthese;

    void parenthese_rec(int);
    void generateParenthesesRec(char [], int, int, int );
    void generateParenthesesIte(int);

    float test(void (*function_p)(int), int n);

#endif
