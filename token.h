#ifndef TOKEN_H
#define TOKEN_H

typedef enum TK_Type {
    TK_IDN,
    TK_EQU,
    TK_STR,
    TK_SMC,
    TK_INT,
    TK_FLT,
    TK_LPA,
    TK_RPA,
    TK_ADD,
    TK_SUB,
    TK_MUL,
    TK_DIV
} TK_Type;

typedef struct Token {
    TK_Type type;
    char* value;
} Token;

void tk_print(Token token) {
    printf("Token([<%i>], %s)\n", token.type, token.value);
}

#endif