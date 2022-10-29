#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defTokens.h"

void match(char* expToken, struct Token actToken){
    if(strcmp(expToken, actToken.Lexema) == 0){
        //printf("son iguales\n");
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", actToken.NumLinea, actToken.NumCol, expToken);
    }
}

void matchTipoToken(char* expTipo, struct Token actToken){
    if(strcmp(expTipo, tipoTokenNames[actToken.Tipo]) == 0){
        //printf("mismo tipo token\n");
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", actToken.NumLinea, actToken.NumCol, expTipo);
    }
}

struct Token getInfoToken(struct nodo *act){
    struct Token tok;
    tok = act->info;
    return tok;
}
