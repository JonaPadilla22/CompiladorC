#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *simbolos = "<_>$=!)(}{:\";.+-*/\\";
char caracter,*ret,*pnt;

int isSimbol(char c){
    ret = strstr(simbolos, pnt);

    if(ret != NULL){
        return 1;
    }else{
        return 0;
    }
}

int isPalabraReservada(FILE* punt){
    int estado = 1;

    char *pals = '|Verdadero|Falso|Entero|Logico|Decimal|Cadena|Por|Tons|';
}

int isEntero(FILE* punt){
    int estado = 1;
    char c = caracter;

    while (estado == 1 || estado == 2 || estado == 3){
          switch (estado) {
            case 1:
                if(isdigit(c)!=0){
                    estado = 3;
                    c = (char)fgetc(punt);
                }else if(c == '+' || c == '-'){
                    estado = 2;
                    c = (char)fgetc(punt);
                }else{
                    estado = 0;
                    break;
                }
              break;
            case 2:
                if(isdigit(c)!=0){
                    estado = 3;
                    c = (char)fgetc(punt);
                }else{
                    estado = 0;
                    break;
                }
              break;
            case 3:
                if(isdigit(c)!=0){
                    estado = 3;
                    c = (char)fgetc(punt);
                }else if (c == ' ' || isSimbol(c)!=0 || c == EOF || c == '\n'){
                    estado = 4;
                    break;
                }
                else{
                    estado = 0;
                    break;
                }
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
                c = (char)fgetc(punt);
              }else{
                  estado = 0;
                  break;
              }
              break;
            case 2:
              if(isalnum(c)!=0){
                estado = 2;
                c = (char)fgetc(punt);
              }else if (c == '_'){
                estado = 3;
                c = (char)fgetc(punt);
              }else if (c == ' ' || c == EOF || isSimbol(c)!=0 || c == '\n'){
                estado = 4;
                break;
              }
              else {
                estado = 0;
                break;
              }
              break;
            case 3:
              if(isalnum(c)!=0){
                estado = 2;
                c = (char)fgetc(punt);
              } else{
                estado = 0;
                break;
              }
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
    //printf("act: %d\n", act);
    fseek(file, act, SEEK_SET);

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

    pnt = &caracter;
    caracter = (char)fgetc(file);
    printf("Linea %d\n", num_lin);
    while (caracter != EOF){

        aux = ftell(file) - 1;

        if(isdigit(caracter)!=0 || caracter == '+' || caracter == '-'){

            if(isEntero(file) == 1){
                printf("es numero");

                lex = lexema(file, aux, ftell(file));
                printf("--- lexema: %s.\n", lex);
            }else{
                //si no lo aceptó el automata, se devuelve el puntero a donde estaba antes de entrar al mismo
                fseek(file, aux, SEEK_SET);

                //mandar al de decimales
                break;

                    //si tampoco se manda al de simbolo
            }

        }
        else if (isalpha(caracter)!=0){
            //else if --- si es letra mandar a de palabra reservada, dentro de (si no es) mandar al de indentificador
            if(isIdentificador(file) == 1){
                printf("es identificador");

                lex = lexema(file, aux, ftell(file));
                printf("--- lexema: %s.\n", lex);
            }else{
                printf("error de sintaxis \n");
                encontrarEspacio(file);
            }

        }//si es simbolo mandar al de simbolo
        else if(isSimbol(caracter)!=0){
            printf("es simbolo");
            lex = lexema(file, aux, ftell(file)+1);
            printf("--- lexema: %s.\n", lex);
        }

        if(caracter=='\n'){
            num_lin++;
            printf("Linea %d\n", num_lin);
            caracter = (char)fgetc(file);
        }

        caracter = (char)fgetc(file);
    }

    fclose(file);

    printf("\n\n");

    system("pause");

    return 0;
}
