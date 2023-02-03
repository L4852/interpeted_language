#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "constants.h"

typedef struct Tokenizer {
    char* src;
    int src_len;
    int pos;
    char current;
    Token* token_list;
} Tokenizer;

int in_string(char target, char* string) {
    int idx = 0;
    while (idx < strlen(string)) {
        if (string[idx] == target) {
            return 1;
        }
        idx++;
    }
    return 0;
}

char* tknz_concat_to_buffer(char* string_a, char new_char) {
    int aLength = strlen(string_a);

    char* combinedBuffer = calloc(aLength + 1, sizeof(char));

    for (int i = 0; i < aLength; i++) {
        combinedBuffer[i] = string_a[i];
    }
    combinedBuffer[aLength] = new_char;

    return combinedBuffer;
}

void tknz_print_token_list(Token* token_list){
    int listSize = (int)(sizeof(token_list) / sizeof(Token));

    printf("%i\n", listSize);

    for (int i=0; i<listSize; i++){
        tk_print(token_list[i]);
    }
}


void tknz_next(Tokenizer* tknz) {
    tknz->pos++;
    if (tknz->pos < tknz->src_len) {
        tknz->current = tknz->src[tknz->pos];
    }
    else {
        tknz->current = '\0';
    }
}
Tokenizer* tknz_init(char* src) {
    Tokenizer* tknz = calloc(1, sizeof(Tokenizer));
    tknz->src = src;
    tknz->pos = -1;
    tknz->src_len = strlen(tknz->src);
    tknz->token_list = calloc(1, sizeof(Token));

    tknz_next(tknz);

    return tknz;
}

void tknz_scan(Tokenizer* tknz) {
    char* numBuffer = calloc(1, sizeof(char));
    int hasDot = 0;

    while (tknz->current != '\0') {
        if (strlen(numBuffer) != 0) {
            if (!(in_string(tknz->current, CONST_NUMERICAL))) {
                // if (!hasDot){
                //     tknz->token_list = 
                // }
                // else{
                //     tknz->token_list = tknz_concat_to_token_list((Token){TK_FLT, numBuffer}, tknz->token_list, (int)(sizeof(tknz->token_list)/sizeof(Token)));
                // }
                memset(numBuffer, '\0', strlen(numBuffer));
                hasDot = 0;
            }
        }
        if (in_string(tknz->current, " \t\n")) {
            tknz_next(tknz);
        }
        else if (in_string(tknz->current, CONST_NUMERICAL)) {
            if (tknz->current == '.') {
                if (!hasDot) {
                    hasDot = 1;
                    numBuffer = tknz_concat_to_buffer(numBuffer, '.');
                }
                else {
                    printf("Invalid character. Scan terminated.\n");
                    exit(0);
                }
            }
            else {
                numBuffer = tknz_concat_to_buffer(numBuffer, tknz->current);
            }
            tknz_next(tknz);
        }
        else {
            tknz_next(tknz);
        }
    }
    tk_print(tknz->token_list[1]);
}

int main() {
    Tokenizer* tknz = tknz_init("593 + 2 * 6;");
    tknz_scan(tknz);
    return 0;
}