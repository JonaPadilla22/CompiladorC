#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "procSintaxis.h"

void operacionAritmetica(){

    if(strcmp("+", token.Lexema)==0){
        match("+");
    }
    else if(strcmp("-", token.Lexema)==0){
        match("-");
    }
    else if(strcmp("*", token.Lexema)==0){
        match("*");
    }
    else if(strcmp("/", token.Lexema)==0){
        match("/");
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION ARITMETICA\n", token.NumLinea, token.NumCol);
        getToken();
    }
}

