//----------------------------------------------------------------
// INICIALIZADOR ENTERO
struct Entero *inicializarEntero()
{
    struct Entero *integer;
    integer = (struct Entero *)malloc(sizeof(struct Entero));
    return integer;
}

//----------------------------------------------------------------
// INICIALIZADOR DECIMAL
struct Decimal *inicializarDecimal()
{
    struct Decimal *decimal;
    decimal = (struct Decimal *)malloc(sizeof(struct Decimal));
    return decimal;
}

//----------------------------------------------------------------
// INICIALIZADOR CADENA
struct Cadena *inicializarCadena()
{
    struct Cadena *cad;
    cad = (struct Cadena *)malloc(sizeof(struct Cadena));
    return cad;
}

/* 
----------------------------------------------------------------
INICIALIZADOR LOGICO
    Token parentesisAbre;
    Token valor;
    Token operacion;
    struct Logico *sigLogico;
    Token parentesisCierra;
*/
struct Logico *inicializarLogico()
{
    struct Logico *logico;
    logico = (struct Logico *)malloc(sizeof(struct Logico));
    return logico;
}

//----------------------------------------------------------------
// INICIALIZADORES SENTENCIA POR
struct SentenciaPor *inicializarSentenciaPor()
{
    struct SentenciaPor *por;
    por = (struct SentenciaPor *)malloc(sizeof(struct SentenciaPor));
    return por;
}

struct Operacion *inicializarOperacion()
{
    struct Operacion *op;
    op = (struct Operacion *)malloc(sizeof(struct Operacion));
    return op;
}

struct Condicion *inicializarCondicion()
{
    struct Condicion *cond;
    cond = (struct Condicion *)malloc(sizeof(struct Condicion));
    return cond;
}

//----------------------------------------------------------------
// INICIALIZADORES SENTENCIA SI
struct SentenciaIf *inicializarSentenciaSi()
{
    struct SentenciaIf *si;
    si = (struct SentenciaIf *)malloc(sizeof(struct SentenciaIf));
    return si;
}

struct Else *inicializarSino()
{
    struct Else *sino;
    sino = (struct Else *)malloc(sizeof(struct Else));
    return sino;
}

//----------------------------------------------------------------
// INICIALIZADOR LEER
struct Leer *inicializarLeer()
{
    struct Leer *leer;
    leer = (struct Leer *)malloc(sizeof(struct Leer));
    return leer;
}

//----------------------------------------------------------------
// INICIALIZADOR ESCRIBIR
struct Escribir *inicializarEscribir()
{
    struct Escribir *escribir;
    escribir = (struct Escribir *)malloc(sizeof(struct Escribir));
    return escribir;
}

//----------------------------------------------------------------
// INICIALIZADOR ASIGNACION
struct Asignacion *inicializarAsignacion()
{
    struct Asignacion *asign;
    asign = (struct Asignacion *)malloc(sizeof(struct Asignacion));
    return asign;
}

//----------------------------------------------------------------
// INICIALIZADOR DECLARACION
struct Declaracion *inicializarDeclaracion()
{
    struct Declaracion *dec;
    dec = (struct Declaracion *)malloc(sizeof(struct Declaracion));
    return dec;
}

//----------------------------------------------------------------
// INICIALIZADOR SENTENCIA
struct Sentencia *inicializarSentencia()
{
    struct Sentencia *sent;
    sent = (struct Sentencia *)malloc(sizeof(struct Sentencia));
    return sent;
}

//----------------------------------------------------------------
// INICIALIZADOR BLOQUE CODIGO
struct BloqueCodigo *inicializarBloqueCodigo()
{
    struct BloqueCodigo *bloque;
    bloque = (struct BloqueCodigo *)malloc(sizeof(struct BloqueCodigo));
    return bloque;
}

//----------------------------------------------------------------
// INICIALIZADOR ESTRUCUTRA GENERAL
struct EstructuraGeneral *inicializarEstructuraGeneral()
{
    struct EstructuraGeneral *estr;
    estr = (struct EstructuraGeneral *)malloc(sizeof(struct EstructuraGeneral));
    return estr;
}