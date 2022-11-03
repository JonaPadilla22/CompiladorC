#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defTokens.h"

int match(char* expToken){
    if(token.Lexema == ""){
        getAnteriorToken();
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expToken);
        getToken();
        return 0;
    }

    if(strcmp(expToken, token.Lexema) == 0){
        getToken();
        return 1;
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expToken);
        return 0;
    }
}

int matchTipoToken(char* expTipo){
    if(token.Lexema == ""){
        getAnteriorToken();
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expTipo);
        getToken();
        return 0;
    }

    if(strcmp(expTipo, tipoTokenNames[token.Tipo]) == 0){
        getToken();
        return 1;
    }else{
        printf("error en la linea %d columna %d, se esperaba %s\n", token.NumLinea, token.NumCol, expTipo);
        return 0;
    }
}
