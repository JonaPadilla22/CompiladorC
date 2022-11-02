#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum TiposSentencias{
    Declaracion,
    Asignacion,
    SentenciaSi,
    SentenciaPor,
    Leer,
    Escribir
};

enum TipoDatos{
    Entero,
    Decimal,
    Cadena,
    Logico
};

struct EstructuraGeneral{
    Token inicio;
    Token parentesisAbre;
    Token parentesisCierra;
    struct BloqueCodigo *siguiente;
};

struct BloqueCodigo{
    Token llaveAbre;
    struct Sentencia *siguiente;
    Token llaveCierra;
};

union tipoSent {
    //tipos de sentencia
    struct SentenciaIf *sentenciaIf;
    struct SentenciaPor *sentenciaPor;
    struct Declaracion *declaracion;
    struct Asignacion *asignacion;
    struct Leer *leer;
    struct Escribir *escribir;
};

union tipoDato {
    struct Entero *entero;
    struct Decimal *decimal;
    struct Cadena *cadena;
    struct Logico *logico;
};

struct Sentencia{
    enum TiposSentencias Tipo;
    struct Sentencia *siguiente; //siguiente sentencia en el mismo bloque de codigo
    union tipoSent sentencia;
};

struct Declaracion{
    int constante; //1 si es constante y 0 si no
    Token nomov;
    enum TipoDatos Tipo;
    struct Asignacion *asignacion;
};

struct Asignacion{
    Token identificador;
    union tipoDato dato;
};

struct SentenciaIf{
    Token si;
    Token parentesisAbre;
    struct Logico *condicion;
    Token parentesisCierra;
    Token tons;
    struct BloqueCodigo *contenido;
    struct ElseIf *elseif;
    struct Else *sino;
};

struct ElseIf{
    Token sino;
    Token parentesisAbre;
    struct Logico *condicion;
    Token parentesisCierra;
    Token tons;
    struct BloqueCodigo *contenido;
    struct ElseIf *elseif;
};

struct Else{
    Token sino;
    struct BloqueCodigo contenido;
};

struct SentenciaPor{
    Token por;
    Token parentesisAbre;
    struct Asignacion *primeraParte;
    Token separador1;
    struct Condicion *cond;
    Token separador2;
    struct Operacion *op;
    Token parentesisCierra;
    struct BloqueCodigo contenido;
};
/*
enum OperacionLogica{
    <=,
    >=,
    <,
    >,
    ==,
    !=,
    and,
    or
};
*/
struct Condicion{
    struct Logico *log1;
    Token opLogica;
    struct Logico *log2;
};
/*
enum OperacionAritmetica{
    +,
    -,
    *,
    /
};
*/
struct Operacion{
    Token identificador;
    Token igual;
    struct Entero *ent1;
    Token opAritmetica;
    struct Entero *ent2;
};

struct Entero {
    Token parentesisAbre;
    Token valorEntero;
    Token opAritmetica;
    struct Entero *sigEntero;
    Token parentesisCierra;
};

struct Logico {
    Token parentesisAbre;
    Token valorLogico;
    Token opLogica;
    struct Logico *sigLogico;
    Token parentesisCierra;
};

struct Decimal {
    Token parentesisAbre;
    Token valorDecimal;
    Token opAritmetica;
    struct Decimal *sigDecimal;
    Token parentesisCierra;
};

struct Cadena {
    Token cadena;
    Token coma;
    struct Cadena *sigCadena;
};

struct Leer {
    Token inicio;
    Token parentesisAbre;
    Token identificador;
    Token parentesisCierra;
};

struct Escribir {
    Token inicio;
    Token parentesisAbre;
    struct Cadena *cad;
    Token parentesisCierra;
};
