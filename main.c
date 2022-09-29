#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "automataDecimal.h"
#include "automataSimbolos.h"

char *simbolos = "<>$=!)(}{:\";+-*/\\";
char caracter,*ret;

int isSimbol(char c){

    if(strchr(simbolos, c) != NULL){
        return 1;
    }else{
        return 0;
    }
}

void concatenarCharACadena(char c, char *cadena)
{
    char cadenaTemporal[2];
    cadenaTemporal[0] = c;
    cadenaTemporal[1] = '\0';
    strcat(cadena, cadenaTemporal);
}

char *concatenarCadenaACadena (char *cadOrig, char *cadDest)
{
    char *cadenaTemporal;
    int y;
    int x;
    for(y = 0; y<strlen(cadDest); y++){
        cadenaTemporal[y] = cadDest[y];
    }
    for(x = 0; x<strlen(cadOrig); x++){
        cadenaTemporal[y+x] = cadOrig[x];
    }
    cadenaTemporal[strlen(cadOrig)+strlen(cadDest)] = '\0';
    return cadenaTemporal;
}

int isPalabraReservada(char* pal){
    char *pals = "|Verdadero|Falso|Entero|Logico|Decimal|Cadena|Por|Tons|";

    char *cad = "|";
    char *aux = concatenarCadenaACadena(pal, cad);
    char *aux2 = concatenarCadenaACadena("|", aux);
    if(strstr(pals, aux2) != NULL){
        return 1;
    }else{
        return 0;
    }

}

int isEntero(FILE* punt){
    int estado = 1;
    char c = caracter;

    while (estado == 1 || estado == 2 || estado == 3){
          switch (estado) {
            case 1:
                if(isdigit(c)!=0){
                    estado = 3;
                }else if(c == '+' || c == '-'){
                    estado = 2;
                }else{
                    estado = 0;
                    break;
                }
                c = (char)fgetc(punt);
              break;
            case 2:
                if(isdigit(c)!=0){
                    estado = 3;
                }else{
                    estado = 0;
                    break;
                }
                c = (char)fgetc(punt);
              break;
            case 3:
                if(isdigit(c)!=0){
                    estado = 3;
                }else if (c == ' ' || isSimbol(c)!=0 || c == EOF || c == '\n'){
                    estado = 4;

                    if(c == '\n'){
                       fseek(punt, -1, SEEK_CUR);
                    }
                    if(c == EOF){
                       fseek(punt, 1, SEEK_CUR);
                    }

                    break;
                }
                else{
                    estado = 0;
                    break;
                }
                c = (char)fgetc(punt);
              break;
        }

    }

    if(estado == 4){
        return 1;
    }else{
        return 0;
    }
}

int isIdentificador (FILE* punt) {
    int estado = 1;
    char c = caracter;

    while (estado == 1 || estado == 2 || estado == 3){
        switch (estado) {
            case 1:
              if(isalpha(c) == 1){
                estado = 2;
              }else{
                  estado = 0;
                  break;
              }
              c = (char)fgetc(punt);
              break;
            case 2:
              if(isalnum(c)!=0){
                estado = 2;
              }else if (c == '_'){
                estado = 3;
              }else if (c == ' ' || c == EOF || isSimbol(c)!=0 || c == '\n'){
                estado = 4;

                if(c == '\n'){
                   fseek(punt, -1, SEEK_CUR);
                }
                if(c == EOF){
                   fseek(punt, 1, SEEK_CUR);
                }

                break;
              }
              else {
                estado = 0;
                break;
              }
              c = (char)fgetc(punt);
              break;
            case 3:
              if(isalnum(c)!=0){
                estado = 2;
              } else{
                estado = 0;
                break;
              }
              c = (char)fgetc(punt);
              break;
        }

    }

    if(estado == 4){
        return 1;
    }else{
        return 0;
    }

}

void encontrarEspacio(FILE* punt) {
    char c = caracter;
    while (c != ' ') {
        c = (char)fgetc(punt);
    }
}

char *lexema (FILE* file, int aux, int act) {
    char* lexema;
    lexema = (char*)malloc(sizeof(char));

    fseek(file, aux, SEEK_SET);

    strcpy(lexema, "");

    fgets(lexema, (act-aux), file);
    fseek(file, act-1, SEEK_SET);

    return lexema + '\0';
}

int main(){
    FILE* file;
    int aux;
    int num_lin = 1;
    char* lex;
    char* a;
    lex = (char*)malloc(sizeof(char));

    if((file = fopen("programa.txt","rt")) == NULL){
        printf("Error al abrir el archivo\n\n");
        system("pause");
        return 0;
    }

    caracter = (char)fgetc(file);
    printf("Linea %d\n", num_lin);
    while (caracter != EOF){

        aux = ftell(file) - 1;

        if(isdigit(caracter)!=0 || caracter == '+' || caracter == '-'){

            if(isEntero(file) == 1){
                printf("es numero");

                lex = lexema(file, aux, ftell(file));
                printf(" --- lexema: %s\n", lex);
            }else{
                //si no lo aceptó el automata, se devuelve el puntero a donde estaba antes de entrar al mismo
                fseek(file, aux, SEEK_SET);

                if(IsNumberDecimal(file) == 1){
                    printf("es numero decimal");

                    lex = lexema(file, aux, ftell(file));
                    printf(" --- lexema: %s\n", lex);
                }else{

                    fseek(file, aux, SEEK_SET);
                    //si tampoco se manda al de simbolo

                }

            }

        }
        else if (isalpha(caracter)!=0){
            //else if --- si es letra mandar a de palabra reservada, dentro de (si no es) mandar al de indentificador
            if(isIdentificador(file) == 1){
                lex = lexema(file, aux, ftell(file));

                if(isPalabraReservada(lex) == 1){
                    printf("es palabra reservada");
                }else{
                    printf("es identificador");
                }

                printf(" --- lexema: %s\n", lex);

            }else{
                printf("error lexico \n");
                encontrarEspacio(file);
            }

        }//si es simbolo mandar al de simbolo
        else if(isSimbol(caracter)!=0){
            printf("es simbolo");
            lex = lexema(file, aux, ftell(file)+1);
            printf(" --- lexema: %s\n", lex);
        }

        caracter = (char)fgetc(file);

        if(caracter=='\n'){
            num_lin++;
            printf("Linea %d\n", num_lin);
            caracter = (char)fgetc(file);
        }


    }

    fclose(file);

    printf("\n\n");

    system("pause");

    return 0;
}
