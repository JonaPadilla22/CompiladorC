void operacion(struct Operacion *op)
{
    op->identificador = token;
    matchTipoToken("ID");
    if (strcmp("++", token.Lexema) == 0 || strcmp("--", token.Lexema) == 0)
    {
        op->opAritmetica = token;
        match(token.Lexema);
    }
    else if (strcmp("=", token.Lexema) == 0)
    {
        op->igual = token;
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

void sentenciaPor(struct SentenciaPor *sentenciaPor)
{
    // INICIO CICLO POR
    sentenciaPor->por = token;
    match("Por");
    sentenciaPor->parentesisAbre = token;
    match("(");
    // DECLARACION ASIGNACION POR
    struct Asignacion *asignacion;
    asignacion = (struct Asignacion *)malloc(sizeof(struct Asignacion));
    sentenciaPor->primeraParte = asignacion;

    asignacion->identificador = token;
    matchTipoToken("ID");
    asignacion->igual = token;
    match("=");
    // ------------------------------------------>
    // declaracion tipo de asignacion
    struct Entero *integer;
    integer = (struct Entero *)malloc(sizeof(struct Entero));
    asignacion->dato.entero = integer;

    entero(integer);

    sentenciaPor->separador1 = token;
    match(":");
    // ------------------------------------------>
    // OPERACION LOGICA CICLO POR
    struct Logico *logic;
    logic = (struct Logico *)malloc(sizeof(struct Logico));
    asignacion->dato.logico = logic;
    logico(logic);

    sentenciaPor->separador1 = token;
    match(":");
    // TERMINA OPERACION LOGICA
    struct Operacion *op;
    op = (struct Operacion *)malloc(sizeof(struct Operacion));
    sentenciaPor->op = op;
    operacion(op);
    sentenciaPor->parentesisCierra = token;
    match(")");
    // bloque_codigo();
}

