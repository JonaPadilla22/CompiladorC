#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estructurasDatos.h"
#include "inicializarEstructuras.h"
#include "estructuras/operaciones.h"
#include "estructuras/generales.h"
/// lista sentencias
// #include "estructuras/sentencia.h"
#include "estructuras/bloqueCodigo.h"
#include "estructuras/sentenciaPor/sentenciaPor.h"
#include "estructuras/sentenciaSi/sentenciaSi.h"
#include "estructuras/sentencia.h"
#include "estructuras/declaracion.h"

void estructura_general()
{
    struct EstructuraGeneral *estructura;
    estructura = malloc(sizeof(struct EstructuraGeneral));

    estructura->inicio = token;
    match("Inicio");

    estructura->parentesisAbre = token;
    match("(");
    estructura->parentesisCierra = token;
    match(")");

    struct BloqueCodigo *bloque;
    bloque = (struct BloqueCodigo *)malloc(sizeof(struct BloqueCodigo));
    estructura->siguiente = bloque;

    bloque_codigo(bloque);

    if (token.Lexema != "")
    {
        printf("error en la linea %d columna %d\n", token.NumLinea, token.NumCol);
    }
}

void leer(struct Leer *ler)
{
    ler->inicio = token;
    match("TintaDentro");
    ler->parentesisAbre = token;
    match("(");
    ler->identificador = token;
    matchTipoToken("ID");
    ler->parentesisCierra = token;
    match(")");
    ler->puntoComa = token;
    match(";");
}

void escribir(struct Escribir *escrib)
{
    escrib->inicio = token;
    match("TintaFuera");
    escrib->parentesisAbre = token;
    match("(");

    struct Cadena *cad;
    cad = malloc(sizeof(struct Cadena));
    escrib->cad = cad;
    cadena(cad);

    escrib->parentesisCierra = token;
    match(")");
    match(";");
}
