#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estructurasDatos.h"

Token sigtok;
Token auxT;
struct nodo *tokAux;

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
    bloque = malloc(sizeof(struct BloqueCodigo));
    estructura->siguiente = bloque;
    bloque_codigo(bloque);

    if (token.Lexema != "")
    {
        printf("error en la linea %d columna %d\n", token.NumLinea, token.NumCol);
    }
}

void bloque_codigo(struct BloqueCodigo bloque)
{

    bloque.llaveAbre = token;
    match("{");

    struct Sentencia *sent;
    sent = malloc(sizeof(struct Sentencia));
    bloque.siguiente = sent;
    lista_sentencias(sent);

    bloque.llaveCierra = token;
    match("}");
}

void lista_sentencias(struct Sentencia sent)
{
    while (strcmp("}", token.Lexema) != 0 && token.Lexema != "")
    {
        sentencia(sent);
        if (strcmp("}", token.Lexema) != 0 && token.Lexema != "")
        {
            struct Sentencia *sent;
            sent = malloc(sizeof(struct Sentencia));
            sent->siguiente = sent;
        }
    }
}

void sentencia(struct Sentencia sent)
{
    // CONDICION
    if (strcmp("Si", token.Lexema) == 0)
    {

        struct SentenciaIf *sentIf;
        sentIf = malloc(sizeof(struct SentenciaIf));
        sent.sentencia.sentenciaIf = sentIf;
        sent.Tipo = SentenciaSi;

        sentenciaSi(sentIf);
        return;
    }

    // CICLO POR
    if (strcmp("Por", token.Lexema) == 0)
    {
        struct SentenciaPor *por;
        por = malloc(sizeof(struct SentenciaPor));
        sentenciaPor(por);
        return;
    }

    // SALIDA
    if (strcmp("TintaFuera", token.Lexema) == 0)
    {
        struct Escribir *escrib;
        escrib = malloc(sizeof(struct Escribir));
        sent.sentencia.escribir = escrib;
        escribir(escrib);
        return;
    }

    // ENTRADA
    if (strcmp("TintaDentro", token.Lexema) == 0)
    {
        struct Leer *lee;
        lee = malloc(sizeof(struct Leer));
        sent.sentencia.leer = lee;
        leer(lee);
        return;
    }

    // DECLARACION
    if (strcmp("Nomoverle", token.Lexema) == 0 ||
        strcmp("Entero", token.Lexema) == 0 ||
        strcmp("Cadena", token.Lexema) == 0 ||
        strcmp("Decimal", token.Lexema) == 0 ||
        strcmp("Logico", token.Lexema) == 0)
    {
        declaracion();
        return;
    }

    // ASINGANCION
    getToken();

    if (strcmp("=", token.Lexema) == 0)
    {
        getAnteriorToken();
        asignacion();
        return;
    }

    printf("Error en la linea %d columna %d\n", token.NumLinea, token.NumCol);
}

int comprobar_final_declaracion()
{
    matchTipoToken("ID");
    if (strcmp(";", token.Lexema) == 0)
        return 1;
    match("=");
    return 0;
}

void declaracion()
{
    // CONSTANTE?
    if (strcmp("Nomoverle", token.Lexema) == 0)
    {
        match("Nomoverle");
    }

    // ENTERO
    if (strcmp("Entero", token.Lexema) == 0)
    {
        match("Entero");

        if (comprobar_final_declaracion() == 1)
            return;

        entero();
        return;
    }

    // DECIMAL
    if (strcmp("Decimal", token.Lexema) == 0)
    {
        match("Decimal");

        if (comprobar_final_declaracion() == 1)
            return;

        decimal();
        return;
    }

    // CADENA
    if (strcmp("Cadena", token.Lexema) == 0)
    {
        match("Cadena");

        if (comprobar_final_declaracion() == 1)
            return;

        cadena();
        return;
    }

    // LOGICO
    if (strcmp("Logico", token.Lexema) == 0)
    {
        match("Logico");

        if (comprobar_final_declaracion() == 1)
            return;

        logico();
        return;
    }
}

void asignacion()
{
    matchTipoToken("ID");
    match("=");
    tipoDato();
    match(";");
}

void operacionLogica()
{
    if (strcmp(">", token.Lexema) == 0)
    {
        match(">");
    }
    else if (strcmp("<", token.Lexema) == 0)
    {
        match("<");
    }
    else if (strcmp("==", token.Lexema) == 0)
    {
        match("==");
    }
    else if (strcmp(">=", token.Lexema) == 0)
    {
        match(">=");
    }
    else if (strcmp("<=", token.Lexema) == 0)
    {
        match("<=");
    }
    else if (strcmp("!=", token.Lexema) == 0)
    {
        match("!=");
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION LOGICA\n", token.NumLinea, token.NumCol);
        getToken();
    }
}

void operacionAritmetica()
{
    if (strcmp("+", token.Lexema) == 0)
    {
        match("+");
    }
    else if (strcmp("-", token.Lexema) == 0)
    {
        match("-");
    }
    else if (strcmp("*", token.Lexema) == 0)
    {
        match("*");
    }
    else if (strcmp("/", token.Lexema) == 0)
    {
        match("/");
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION ARITMETICA\n", token.NumLinea, token.NumCol);
        getToken();
    }
}

int entero()
{
    if (strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            matchTipoToken("NUMERO");
            operacionAritmetica();
            entero();
        }
        else
        {
            matchTipoToken("NUMERO");
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            matchTipoToken("ID");
            operacionAritmetica();
            entero();
        }
        else
        {
            matchTipoToken("ID");
        }
    }
    else if (strcmp("(", token.Lexema) == 0)
    {
        match("(");
        entero();
        match(")");
        sigtok = getInfoToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            operacionAritmetica();
            entero();
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba ENTERO\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int decimal()
{
    if (strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            matchTipoToken("NUMERO");
            operacionAritmetica();
            entero();
        }
        else
        {
            matchTipoToken("NUMERO");
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            matchTipoToken("ID");
            operacionAritmetica();
            entero();
        }
        else
        {
            matchTipoToken("ID");
        }
    }
    else if (strcmp("(", token.Lexema) == 0)
    {
        match("(");
        entero();
        match(")");
        sigtok = getInfoToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            operacionAritmetica();
            entero();
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba DECIMAL\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int cadena()
{
    if (strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0)
    {
        matchTipoToken("CADENA");
        if (strcmp(",", token.Lexema) == 0)
        {
            match(",");
            cadena();
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        matchTipoToken("ID");
        if (strcmp(",", token.Lexema) == 0)
        {
            match(",");
            cadena();
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba CADENA\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}

int logico()
{

    if (strcmp("(", token.Lexema) == 0)
    {
        match("(");
        logico();
        match(")");
    }

    if (strcmp("Verdadero", token.Lexema) == 0)
    {
        match("Verdadero");
        return 1;
    }

    if (strcmp("Falso", token.Lexema) == 0)
    {
        match("Falso");
        return 1;
    }

    if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0 || strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0 || strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp(">", sigtok.Lexema) == 0 || strcmp("<", sigtok.Lexema) == 0 || strcmp("==", sigtok.Lexema) == 0 || strcmp(">=", sigtok.Lexema) == 0 || strcmp("<=", sigtok.Lexema) == 0 || strcmp("!=", sigtok.Lexema) == 0)
        {
            match(token.Lexema);
            operacionLogica();
            logico();
        }
        else if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            match(token.Lexema);
            operacionAritmetica();
            entero();
        }
        else
        {
            match(token.Lexema);
        }
        return 1;
    }

    if (strcmp(">", token.Lexema) == 0 || strcmp("<", token.Lexema) == 0 || strcmp("==", token.Lexema) == 0 || strcmp(">=", token.Lexema) == 0 || strcmp("<=", token.Lexema) == 0 || strcmp("!=", token.Lexema) == 0)
    {
        match(token.Lexema);
        logico();
        return 1;
    }

    if (strcmp("&&", token.Lexema) == 0 || strcmp("||", token.Lexema) == 0)
    {
        match(token.Lexema);
        return 1;
    }

    if (strcmp(";", token.Lexema) == 0)
    {
        return;
    }

    printf("error en la linea %d columna %d, se esperaba VALOR LOGICO\n", token.NumLinea, token.NumCol);
    return 0;
}

void leer(struct Leer leer)
{
    match("TintaDentro");
    match("(");
    matchTipoToken("ID");
    match(")");
    match(";");
}

void escribir(struct Escribir escrib)
{
    escrib.inicio = token;
    match("TintaFuera");
    escrib.parentesisAbre = token;
    match("(");

    struct Cadena *cad;
    cad = malloc(sizeof(struct Cadena));
    escrib.cad = cad;
    cadena(cad);

    escrib.parentesisCierra = token;
    match(")");
    match(";");
}

void sentenciaPor(struct SentenciaPor *sentenciaPor)
{
    // INICIO CICLO POR
    sentenciaPor.por = token;
    match("Por");
    sentenciaPor.parentesisAbre = token;
    match("(");
    // DECLARACION ASIGNACION POR
    struct Asignacion *asignacion;
    asignacion = (struct Asignacion *)malloc(sizeof(struct Asignacion));
    sentenciaPor.asignacion = asignacion;

    asignacion.identificador = token
    matchTipoToken("ID");
    asignacion.igual = token;
    match("=");
    // ------------------------------------------>
    // declaracion tipo de asignacion
    struct Entero *integer;
    integer = (struct Entero *)malloc(sizeof(struct Entero));
    asignacion.dato.Entero = integer;

    entero(integer);

    sentenciaPor.separador1 = token;
    match(":");
    // ------------------------------------------>
    // OPERACION LOGICA CICLO POR
    struct Logico *logic;
    logic = (struct Logico *)malloc(sizeof(struct Logico));
    asignacion.dato.Logico = logic;
    logico(logic);

    sentenciaPor.separador1 = token;
    match(":");
    // TERMINA OPERACION LOGICA
    struct Operacion *op;
    op = (struct Operacion *)malloc(sizeof(struct Operacion));
    sentenciaPor.op = op;
    operacion(op);
    sentenciaPor.parentesisCierra = token;
    match(")");
    // bloque_codigo();
}

void operacion(struct Operacion *op)
{
    op.identificador = token;
    matchTipoToken("ID");
    if (strcmp("++", token.Lexema) == 0 || strcmp("--", token.Lexema) == 0)
    {
        op.opAritmetica = token;
        match(token.Lexema);
    }
    else if (strcmp("=", token.Lexema) == 0)
    {
        op.igual = token;
        match("=");
        struct Entero *integer;
        integer = (struct Entero *)malloc(sizeof(struct Entero));
        op->entero = integer;
        entero(integer);
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba OPERACION\n", token.NumLinea, token.NumCol);
    }
}

void sentenciaSi(struct SentenciaIf sentIf)
{
    sentIf.nombre = token;
    match("Si");
    sentenciaSiCondicion(sentIf);
}

void sentenciaSiCondicion(struct SentenciaIf sentIf)
{
    sentIf.parentesisAbre = token;
    match("(");
    struct Logico *logic;
    logic = (struct Logico *)malloc(sizeof(struct Logico));
    sentIf.condicion = logic;
    logico(logic);
    sentIf.parentesisCierra = token;
    match(")");
    sentIf.tons = token;
    match("Tons");
    //
    struct BloqueCodigo bloque;
    // bloque = (struct BloqueCodigo *)malloc(sizeof(struct BloqueCodigo));
    sentIf.contenido = &bloque;
    bloque_codigo(bloque);

    if (strcmp("Sino", token.Lexema) == 0)
    {

        match("Sino");
        if (strcmp("(", token.Lexema) == 0)
        {
            struct ElseIf elseIf;

            sentIf.elseif = &elseIf;
            // sentenciaSiCondicion();
        }
        else
        {
            struct BloqueCodigo bloque;
            // bloque_codigo();
        }
    }
}

void tipoDato()
{
    auxT = getInfoToken();
    tokAux = tokAct;
    int x = 0;
    if (strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0)
    {
        matchTipoToken("CADENA");
        return;
    }

    while (strcmp(";", token.Lexema) != 0)
    {
        getToken();
        if (strcmp(">", token.Lexema) == 0 ||
            strcmp("<", token.Lexema) == 0 ||
            strcmp("==", token.Lexema) == 0 ||
            strcmp(">=", token.Lexema) == 0 ||
            strcmp("<=", token.Lexema) == 0 ||
            strcmp("!=", token.Lexema) == 0)
        {
            x = 1;
            break;
        }
    }

    token = auxT;
    tokAct = tokAux;

    if (x == 1)
    {
        logico();
        return;
    }
    else
    {
        entero();
        return;
    }

    printf("error en la linea %d columna %d, se esperaba TIPO DATO\n", token.NumLinea, token.NumCol);
}
