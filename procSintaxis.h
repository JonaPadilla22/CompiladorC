#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defTokens.h"

void match(char* expToken){
    if(strcmp(expToken, token.Lexema) == 0){
        getToken();
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expToken);
    }
}

void matchTipoToken(char* expTipo){
    if(strcmp(expTipo, tipoTokenNames[token.Tipo]) == 0){
        getToken();
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expTipo);
    }
}
