#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

enum TipoToken
{
    PalRes,
    id,
    num,
    sim
};

struct Token
{
    //char Nombre[80];
    enum TipoToken Tipo;
    char Lexema[];
    int Valor;
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

int main()
{
    printf("Hello world!\n");
    return 0;
}
