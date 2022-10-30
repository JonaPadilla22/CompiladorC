#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "procSintaxis.h"

struct Token sigtok;
struct Token auxT;
struct nodo *tokAux;

void estructura_general(){
    match("Inicio");
    match("(");
    match(")");
    bloque_codigo();
}

void bloque_codigo(){
    match("{");
    lista_sentencias();
    //printf("sale lis sent\n");
    //printf("tok: %s\n", token.Lexema);
    match("}");
}

void lista_sentencias(){
    while(strcmp("}", token.Lexema)!=0){
        sentencia();
    }
}

void sentencia(){
    // printf("Token en sentencia: %s.\n", token.Lexema);
    // CONDICION
    if(strcmp("Si", token.Lexema)==0){
        //printf("Entre a sentencia if %s",token.Lexema);
        sentenciaSi();
        return;
    }

    //CICLO POR
    if(strcmp("Por", token.Lexema)==0){
        sentenciaPor();
        return;
    }

    //SALIDA
    if(strcmp("TintaFuera", token.Lexema)==0){
        escribir();
        return;
    }

    //ENTRADA
    if(strcmp("TintaDentro", token.Lexema)==0){
        leer();
        return;
    }

    //DECLARACION
    if(strcmp("Nomoverle", token.Lexema)==0 ||
       strcmp("Entero", token.Lexema)==0 ||
       strcmp("Cadena", token.Lexema)==0 ||
       strcmp("Decimal", token.Lexema)==0 ||
       strcmp("Logico", token.Lexema)==0
       ){
        declaracion();
        return;
       }

    // ASINGANCION
    getToken();

    if(strcmp("=", token.Lexema)==0){
        getAnteriorToken();
        asignacion();
        return;
    }

    system("pause");
    //ERROR?
    printf("Error en la linea %d columna %d\n", token.NumLinea, token.NumCol);

}

int comprobar_final_declaracion(){
    matchTipoToken("ID");

    if(strcmp(";", token.Lexema)==0) return 1;

    match("=");
    return 0;
}

void declaracion(){
    //CONSTANTE?
    if(strcmp("Nomoverle", token.Lexema)==0){
        match("Nomoverle");
    }

    //ENTERO
    if(strcmp("Entero", token.Lexema)==0){
        match("Entero");

        if(comprobar_final_declaracion()==1) return;

        entero();
        return;
    }

    //DECIMAL
    if(strcmp("Decimal", token.Lexema)==0){
        match("Decimal");

        if(comprobar_final_declaracion()==1) return;

        decimal();
        return;
    }

    //CADENA
    if(strcmp("Cadena", token.Lexema)==0){
        match("Cadena");

        if(comprobar_final_declaracion()==1) return;

        cadena();
        return;
    }

    //LOGICO
    if(strcmp("Logico", token.Lexema)==0){
        match("Logico");

        if(comprobar_final_declaracion()==1) return;

        logico();
        return;
    }

}

void asignacion(){

    matchTipoToken("ID");
    match("=");

    tipoDato();
    match(";");
}

//PARTE 2
void operacionLogica(){
    if(strcmp(">", token.Lexema)==0){
        match(">");
    }
    else if(strcmp("<", token.Lexema)==0){
        match("<");
    }
    else if(strcmp("==", token.Lexema)==0){
        match("==");
    }
    else if(strcmp(">=", token.Lexema)==0){
        match(">=");
    }
    else if(strcmp("<=", token.Lexema)==0){
        match("<=");
    }
    else if(strcmp("!=", token.Lexema)==0){
        match("!=");
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION LOGICA\n", token.NumLinea, token.NumCol);
        getToken();
    }
}

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

int entero(){
    if(strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0){
        sigtok = getInfoSigToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            matchTipoToken("NUMERO");
            operacionAritmetica();
            entero();
        }else{
            matchTipoToken("NUMERO");
        }
    }
    else if(strcmp("ID", tipoTokenNames[token.Tipo]) == 0){
        sigtok = getInfoSigToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            matchTipoToken("ID");
            operacionAritmetica();
            entero();
        }else{
            matchTipoToken("ID");
        }
    }
    else if(strcmp("(", token.Lexema) == 0){
        match("(");
        entero();
        match(")");
        sigtok = getInfoToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            operacionAritmetica();
            entero();
        }
    }
    else{
        printf("error en la linea %d columna %d, se esperaba ENTERO\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int decimal(){
    if(strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0){
        sigtok = getInfoSigToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            matchTipoToken("NUMERO");
            operacionAritmetica();
            entero();
        }else{
            matchTipoToken("NUMERO");
        }
    }
    else if(strcmp("ID", tipoTokenNames[token.Tipo]) == 0){
        sigtok = getInfoSigToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            matchTipoToken("ID");
            operacionAritmetica();
            entero();
        }else{
            matchTipoToken("ID");
        }
    }
    else if(strcmp("(", token.Lexema) == 0){
        match("(");
        entero();
        match(")");
        sigtok = getInfoToken();
        if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0){
            operacionAritmetica();
            entero();
        }
    }
    else{
        printf("error en la linea %d columna %d, se esperaba DECIMAL\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int cadena(){
    if(strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0){
      matchTipoToken("CADENA");
      if(strcmp(",", token.Lexema)==0){
        match(",");
        cadena();
      }
    }
    else if(strcmp("ID", tipoTokenNames[token.Tipo]) == 0){
      matchTipoToken("ID");
      if(strcmp(",", token.Lexema)==0){
        match(",");
        cadena();
      }
    }
    else{
        printf("error en la linea %d columna %d, se esperaba CADENA\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int logico() {

    if(strcmp("(", token.Lexema) == 0){
        match("(");
        logico();
        match(")");
    }

    if(strcmp("Verdadero", token.Lexema)==0){
        match("Verdadero");
        return 1;
    }


    if(strcmp("Falso", token.Lexema)==0){
        match("Falso");
        return 1;
    }

    if(strcmp("ID", tipoTokenNames[token.Tipo]) == 0 || strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0 || strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0){
        sigtok = getInfoSigToken();
        if(strcmp(">", sigtok.Lexema) == 0 || strcmp("<", sigtok.Lexema) == 0 || strcmp("==", sigtok.Lexema) == 0 || strcmp(">=", sigtok.Lexema) == 0 || strcmp("<=", sigtok.Lexema) == 0 || strcmp("!=", sigtok.Lexema) == 0){
            match(token.Lexema);
            operacionLogica();
            logico();
        }
        else if(strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema)==0){
            match(token.Lexema);
            operacionAritmetica();
            entero();
        }
        else{
            match(token.Lexema);
        }
        return 1;
    }

    if(strcmp(">", token.Lexema) == 0 || strcmp("<", token.Lexema) == 0 || strcmp("==", token.Lexema) == 0 || strcmp(">=", token.Lexema) == 0 || strcmp("<=", token.Lexema) == 0 || strcmp("!=", token.Lexema) == 0){
        match(token.Lexema);
        logico();
        return 1;
    }

    if(strcmp("&&", token.Lexema)==0 || strcmp("||", token.Lexema)==0){
        match(token.Lexema);
        return 1;
    }

    if(strcmp(";", token.Lexema) == 0){
        return;
    }

    printf("error en la linea %d columna %d, se esperaba VALOR LOGICO\n", token.NumLinea, token.NumCol);
    return 0;

}

void leer(){
    match("TintaDentro");
    match("(");
    matchTipoToken("ID");
    match(")");
    match(";");
}

void escribir(){
    match("TintaFuera");
    match("(");
    cadena();
    match(")");
    match(";");
}

void sentenciaPor(){
    match("Por");
    match("(");
    matchTipoToken("ID");
    match("=");
    entero();
    match(":");
    logico();
    match(":");
    operacion();
    match(")");
    bloque_codigo();
}

void operacion() {
    matchTipoToken("ID");
    if(strcmp("++", token.Lexema)==0 || strcmp("--", token.Lexema)==0){
        match(token.Lexema);
    }
    else if(strcmp("=", token.Lexema)==0){
        match("=");
        entero();
    }else{
        printf("error en la linea %d columna %d, se esperaba OPERACION\n", token.NumLinea, token.NumCol);
    }
}

void sentenciaSi(){
    match("Si");
    sentenciaSiCondicion();
}

void sentenciaSiCondicion(){
    match("(");
    logico();
    match(")");
    match("Tons");
    if(strcmp("{", token.Lexema)==0){
        bloque_codigo();
    }
    else if(strcmp("Sino", token.Lexema)==0){
        match("Sino");
        if(strcmp("{", token.Lexema)==0){
            bloque_codigo();
        }
        else if(strcmp("(", token.Lexema)==0){
            sentenciaSiCondicion();
        }
        else{
            bloque_codigo();
        }
    }
}

void tipoDato() {
    auxT = getInfoToken();
    tokAux = tokAct;
    int x = 0;
    if(strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0){
        matchTipoToken("CADENA");
        return;
    }

    while(strcmp(";", token.Lexema) != 0){
        getToken();
        if(strcmp(">", token.Lexema) == 0 || strcmp("<", token.Lexema) == 0 || strcmp("==", token.Lexema) == 0 || strcmp(">=", token.Lexema) == 0 || strcmp("<=", token.Lexema) == 0 || strcmp("!=", token.Lexema) == 0){
            x = 1;
            break;
        }
    }

    token = auxT;
    tokAct = tokAux;

    if(x==1){
        logico();
        return;
    }else{
        entero();
        return;
    }


    printf("error en la linea %d columna %d, se esperaba TIPO DATO\n", token.NumLinea, token.NumCol);

}

