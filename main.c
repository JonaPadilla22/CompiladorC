#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "automataDecimal.h"
#include "automataCadenas.h"

char *simbolos = "<>$=!)(}{:\";+-*/\\";
char caracter,*ret;
int num_lin = 1;
long col_ac = 0;
const char* tipoTokenNames[] = {"PALABRA RESERVADA", "ID", "NUMERO", "SIMBOLO", "CADENA"};


enum TipoToken
{
    PalRes,
    id,
    num,
    sim,
    cad
};

struct Token
{
    //char Nombre[80];
    enum TipoToken Tipo;
    char *Lexema;
    int Valor;
    int NumLinea;
};

struct nodo
{
    struct Token info;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *raiz;
struct nodo *actual;

void insertar(struct Token token)
{
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));

    nuevo->info = token;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    if (raiz == NULL)
    {
        raiz = nuevo;
        actual = nuevo;
    }
    else
    {
        nuevo->izq = actual;
        actual->der = nuevo;
        actual = nuevo;
    }
}

void imprimirlista(struct nodo *inicio){
    printf("\n------------LISTA ENLAZADA------------\n");
    struct nodo *act;
    act=inicio;
    int elem = 0;
    while(act!=NULL){
        printf("\nELEMENTO %d\n", elem),
        printf("Tipo: %s\n", tipoTokenNames[act->info.Tipo]);
        printf("Lexema: %s\n", act->info.Lexema);
        printf("Valor: %d\n", act->info.Valor);
        printf("Linea: %d\n", act->info.NumLinea);
        act=act->der;
        elem++;
    }
}

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

void contarLinea(FILE* file){
    num_lin++;
    printf("Linea %d\n", num_lin);
    //caracter = (char)fgetc(file);
    col_ac = ftell(file) - 1;
}

void encontrarEspacio(FILE* punt) {
    char c = caracter;
    while (c != ' ' && c != '\n') {
        c = (char)fgetc(punt);
    }
    if(c == '\n'){
        contarLinea(punt);
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

                struct Token t;
                t.Lexema = lex;
                t.NumLinea = num_lin;
                t.Valor = atoi(lex);
                t.Tipo = num;
                insertar(t);

            }else{
                //si no lo aceptó el automata, se devuelve el puntero a donde estaba antes de entrar al mismo
                fseek(file, aux, SEEK_SET);

                if(IsNumberDecimal(file) == 1){
                    printf("es numero decimal");

                    lex = lexema(file, aux, ftell(file));
                    printf(" --- lexema: %s\n", lex);

                    struct Token t;
                    t.Lexema = lex;
                    t.NumLinea = num_lin;
                    t.Tipo = num;
                    t.Valor = atof(lex);
                    insertar(t);
                }else{

                    fseek(file, aux, SEEK_SET);
                    caracter = (char)fgetc(file);
                    //si tampoco se manda al de simbolo
                    if(isSimbol(caracter)!=0){

                        if(caracter=='"'){
                            fseek(file, -1, SEEK_CUR);
                            if(isCadena(file)!=0){
                                printf("es cadena");
                                lex = lexema(file, aux, ftell(file)+1);
                                printf(" --- lexema: %s\n", lex);

                                struct Token t;
                                t.Lexema = lex;
                                t.NumLinea = num_lin;
                                t.Tipo = cad;
                                t.Valor = 0;
                                insertar(t);
                            }else{
                                int col_err = aux - col_ac + 1;
                                printf("error lexico en la columna %d\n", col_err);
                                fseek(file, -1, SEEK_CUR);
                            }
                        }else{
                            printf("es simbolo");
                            lex = lexema(file, aux, ftell(file)+1);
                            printf(" --- lexema: %s\n", lex);

                            struct Token t;
                            t.Lexema = lex;
                            t.NumLinea = num_lin;
                            t.Tipo = sim;
                            t.Valor = 0;
                            insertar(t);
                        }

                    }else{
                        int col_err = aux - col_ac + 1;
                        printf("error lexico en la columna %d\n", col_err);
                        encontrarEspacio(file);
                    }


                }

            }

        }
        else if (isalpha(caracter)!=0){
            //else if --- si es letra mandar a de palabra reservada, dentro de (si no es) mandar al de indentificador
            if(isIdentificador(file) == 1){
                lex = lexema(file, aux, ftell(file));
                struct Token t;
                if(isPalabraReservada(lex) == 1){
                    printf("es palabra reservada");
                    t.Tipo = PalRes;
                }else{
                    printf("es identificador");
                    t.Tipo = id;
                }

                printf(" --- lexema: %s\n", lex);


                t.Lexema = lex;
                t.NumLinea = num_lin;
                t.Valor = 0;
                insertar(t);
            }else{
                int col_err = aux - col_ac + 1;
                printf("error lexico en la columna %d\n", col_err);
                encontrarEspacio(file);
                //fseek(file, 1, SEEK_CUR);
            }

        }//si es simbolo mandar al de simbolo
        else if(isSimbol(caracter)!=0){

            if(caracter=='"'){
                fseek(file, -1, SEEK_CUR);
                if(isCadena(file)!=0){
                    printf("es cadena");
                    lex = lexema(file, aux, ftell(file)+1);
                    printf(" --- lexema: %s\n", lex);

                    struct Token t;
                    t.Lexema = lex;
                    t.NumLinea = num_lin;
                    t.Tipo = cad;
                    t.Valor = 0;
                    insertar(t);
                }else{
                    int col_err = aux - col_ac + 1;
                    printf("error lexico en la columna %d\n", col_err);
                    fseek(file, -1, SEEK_CUR);
                }
            }else{
                printf("es simbolo");
                lex = lexema(file, aux, ftell(file)+1);
                printf(" --- lexema: %s\n", lex);

                struct Token t;
                t.Lexema = lex;
                t.NumLinea = num_lin;
                t.Tipo = sim;
                t.Valor = 0;
                insertar(t);
            }

        }

        caracter = (char)fgetc(file);

        if(caracter=='\n'){
            contarLinea(file);
        }


    }

    imprimirlista(raiz);

    fclose(file);

    printf("\n\n");

    system("pause");

    return 0;
}
