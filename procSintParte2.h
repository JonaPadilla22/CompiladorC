#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "procSintaxis.h"

void operacionAritmetica(struct Token token){

    if(strcmp("+", token.Lexema)==0){
        match("+", token);
    }
    else if(strcmp("-", token.Lexema)==0){
        match("-", token);
    }
    else if(strcmp("*", token.Lexema)==0){
        match("*", token);
    }
    else if(strcmp("/", token.Lexema)==0){
        match("/", token);
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION ARITMETICA\n", token.NumLinea, token.NumCol);
    }
}
