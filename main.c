/*
    AUTORES:
        PADILLA JARAMILLO JONATHAN
        SAUCEDA RUIZ HECTOR EDUARDO
    GRUPO: 401 SOFTWARE
    FECHA: 30/SEPTIEMBRE/2022
    NOMBRE: COMPILADOR FASE LEXICO
    DESCRIPCION: AVANCE DE COMPILADOR EN SU FASE LEXICA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "automataDecimal.h"
#include "automataCadenas.h"
#include "automataEntero.h"
#include "automataSimbolos.h"

#include "procSintParte2.h"

char *simbolos = "<>$=!),(}{:\";+-*/\\&|";
char caracter, *ret;
int num_lin = 1;
long col_ac = 0;
int aux;
char *lex;
// const char* tipoTokenNames[] = {"PALABRA RESERVADA", "ID", "NUMERO", "SIMBOLO", "CADENA"};

int isSimbol(char c)
{

    if (strchr(simbolos, c) != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct nodo *raiz;
struct nodo *actual;

void insertar(struct Token token)
{
    struct nodo *nuevo;
    //FIXME: malloc do not working properly here
    nuevo = malloc(10*sizeof(struct nodo));

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

void imprimirlista(struct nodo *inicio)
{
    printf("\n------------LISTA ENLAZADA------------\n");
    struct nodo *act;
    act = inicio;
    int elem = 0;
    while (act != NULL)
    {
        printf("\nELEMENTO %d\n", elem + 1),
            printf("Tipo: %s\n", tipoTokenNames[act->info.Tipo]);
        printf("Lexema: %s\n", act->info.Lexema);
        printf("Valor: %d\n", act->info.Valor);
        printf("Linea: %d\n", act->info.NumLinea);
        printf("Columna: %d\n", act->info.NumCol);
        act = act->der;
        elem++;
    }
}

char *concatenarCadenaACadena(char *cadOrig, char *cadDest)
{
    char *cadenaTemporal;
    int y;
    int x;
    for (y = 0; y < strlen(cadDest); y++)
    {
        cadenaTemporal[y] = cadDest[y];
    }
    for (x = 0; x < strlen(cadOrig); x++)
    {
        cadenaTemporal[y + x] = cadOrig[x];
    }
    cadenaTemporal[strlen(cadOrig) + strlen(cadDest)] = '\0';
    return cadenaTemporal;
}

int isPalabraReservada(char *pal)
{
    char *pals = "|Inicio|Verdadero|Falso|Entero|Logico|Decimal|Cadena|Nomoverle|Por|Si|Tons|Sino|TintaFuera|TintaDentro|Romper|Continuar";
    // printf("-");
    char pipe[2] = "|\0";
    char cad[30];
    // printf("siuuuuu");
    // char *aux = concatenarCadenaACadena(pal, cad);
    // char *aux2 = concatenarCadenaACadena("|", aux);

    strcpy(cad, pipe);
    strcat(cad, pal);
    strcat(cad, pipe);

    // printf("\nCadena generada: %s\n", cad);

    if (strstr(pals, cad) != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isIdentificador(char *str)
{
    int estado = 1;
    int numc = 0;
    char c = str[numc];
    while (estado == 1 || estado == 2 || estado == 3)
    {
        switch (estado)
        {
        case 1:
            if (isalpha(c) == 1)
            {
                estado = 2;
            }
            else
            {
                estado = 0;
                break;
            }
            numc++;
            c = str[numc];
            break;
        case 2:
            if (isalnum(c) != 0)
            {
                estado = 2;
            }
            else if (c == '_')
            {
                estado = 3;
            }
            else if (c == '\0' || isSimbol(c) != 0 || c == '\n')
            {
                estado = 4;
                break;
            }
            else
            {
                estado = 0;
                break;
            }
            numc++;
            c = str[numc];
            break;
        case 3:
            if (isalnum(c) != 0)
            {
                estado = 2;
            }
            else
            {
                estado = 0;
                break;
            }
            numc++;
            c = str[numc];
            break;
        }
    }

    if (estado == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void contarLinea(FILE *file)
{
    num_lin++;
    col_ac = ftell(file);
    printf("--------------Linea %d--------------\n", num_lin);
}

int getColAct(int aux)
{
    int col;
    col = aux - col_ac;
    return col;
}

char *formarTokenSimbol(FILE *file)
{
    char *tokenString;
    int num_c = 0;
    tokenString = (char *)malloc(sizeof(char));
    tokenString[num_c] = caracter;
    num_c++;
    caracter = (char)fgetc(file);
    while (isSimbol(caracter) && caracter != '(' && caracter != ')' && caracter != '{' && caracter != '}' && caracter != ';' && caracter != '"')
    {
        tokenString[num_c] = caracter;
        num_c++;
        caracter = (char)fgetc(file);
    }
    tokenString[num_c] = '\0';
    return tokenString;
}

char *formarTokenNoSimbol(FILE *file)
{
    char *tokenString;
    int num_c = 0;
    tokenString = (char *)malloc(sizeof(char));
    tokenString[num_c] = caracter;
    num_c++;
    caracter = (char)fgetc(file);
    while ((caracter != EOF) && (caracter != '\n') && (caracter != ' ') && (isSimbol(caracter) == 0))
    {
        tokenString[num_c] = caracter;
        num_c++;
        if (isSimbol(caracter) == 1)
        {
            printf("A");
            break;
        }
        caracter = (char)fgetc(file);
    }
    tokenString[num_c] = '\0';
    return tokenString;
}

int main()
{
    FILE *file;
    char *char_leido;
    int tok_valid = 0;
    int is_tok_cad = 0;
    int aux;
    struct Token t;

    do
    {
        num_lin = 1;
        col_ac = 0;

        if ((file = fopen("programa.txt", "rt")) == NULL)
        {
            printf("Error al abrir el archivo\n\n");
            system("pause");
            return 0;
        }

        caracter = (char)fgetc(file);
        printf("--------------Linea %d--------------\n", num_lin);
        while (caracter != EOF)
        {
            aux = ftell(file);
            if (caracter == '\n')
            {
                contarLinea(file);
            }

            if (caracter == '\n' || caracter == ' ' || caracter == '\t')
            {
                caracter = (char)fgetc(file);
            }

            if (isSimbol(caracter))
            {
                if (caracter == '"')
                {
                    int cad_valid = 0;
                    int nc = 0;
                    lex = (char *)malloc(sizeof(char));
                    lex[nc] = caracter;
                    caracter = (char)fgetc(file);
                    while (caracter != '\n')
                    {
                        nc++;
                        lex[nc] = caracter;
                        if (caracter == '"' && lex[nc - 1] != '\\')
                        {
                            cad_valid = 1;
                            caracter = (char)fgetc(file);
                            break;
                        }
                        caracter = (char)fgetc(file);
                    }

                    if (cad_valid == 1)
                    {
                        printf("TOKEN: %s (cadena)\n", lex);
                        tok_valid = 1;
                        t.Valor = 0;
                        t.Tipo = cad;
                    }
                    else
                    {
                        printf("CADENA INVALIDA\n");
                        tok_valid = 0;
                    }
                }
                else
                {
                    lex = formarTokenSimbol(file);
                    if (isSimbolToken(lex) == 1)
                    {
                        printf("TOKEN: %s (simbolo)\n", lex);
                        tok_valid = 1;
                        t.Valor = 0;
                        t.Tipo = sim;
                    }
                    else
                    {
                        printf("TOKEN NO VALIDO: %s\n", lex);
                        tok_valid = 0;
                    }
                }
            }
            else if (isalnum(caracter) || caracter == '.')
            {
                lex = formarTokenNoSimbol(file);

                if (isIdentificador(lex) == 1)
                {
                    if (isPalabraReservada(lex) == 1)
                    {
                        printf("TOKEN: %s (palabra reservada)\n", lex);
                        tok_valid = 1;
                        t.Valor = 0;
                        t.Tipo = PalRes;
                    }
                    else
                    {
                        printf("TOKEN: %s (identificador)\n", lex);
                        tok_valid = 1;
                        t.Valor = 0;
                        t.Tipo = id;
                    }
                }
                else if (isEntero(lex) == 1)
                {
                    printf("TOKEN: %s (num entero)\n", lex);
                    tok_valid = 1;
                    t.Valor = atoi(lex);
                    t.Tipo = num;
                }
                else if (IsNumberDecimal(lex) == 1)
                {
                    printf("TOKEN: %s (num decimal)\n", lex);
                    tok_valid = 1;
                    t.Valor = atof(lex);
                    t.Tipo = num;
                }
                else
                {
                    printf("TOKEN NO VALIDO: %s\n", lex);
                    tok_valid = 0;
                }
            }

            if (tok_valid == 1)
            {
                t.Lexema = lex;
                t.NumLinea = num_lin;
                t.NumCol = getColAct(aux);
                insertar(t);
            }
            // printf("Repitiendo = %s\n", lex);
        }

        // imprimirlista(raiz);
        printf("\n\n");
        tokAct = raiz;
        token = getInfoToken(tokAct); // obtiene la info del token raiz

        printf("Lexema tok: %s\n", token.Lexema);
        matchTipoToken("ID");

        printf("Lexema tok: %s\n", token.Lexema);
        match("!=");

        printf("Lexema tok: %s\n", token.Lexema);
        matchTipoToken("CADENA");

        printf("Lexema tok: %s\n", token.Lexema);
        operacionAritmetica();

        fclose(file);

        printf("\n\n");

        system("pause");

        char_leido = "\n";
        raiz = NULL;
        system("cls");
    } while (char_leido == "\n");

    return 0;
}
