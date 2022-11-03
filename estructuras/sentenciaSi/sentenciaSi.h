

void sentenciaSiCondicion(struct SentenciaIf *sentIf)
{
    sentIf->parentesisAbre = token;
    match("(");
    struct Logico *logic = inicializarLogico();
    sentIf->condicion = logic;
    logico(logic);
    sentIf->parentesisCierra = token;
    match(")");
    sentIf->tons = token;
    match("Tons");
    //
    struct BloqueCodigo *bloque = inicializarBloqueCodigo();
    sentIf->contenido = bloque;
    bloque_codigo(bloque);

    if (strcmp("Sino", token.Lexema) == 0)
    {
        sentIf->nombre = token;
        match("Sino");
        if (strcmp("(", token.Lexema) == 0)
        {
            struct SentenciaIf *elseIf = inicializarSentenciaSi();
            sentIf->sino.tons = elseIf;
            sentenciaSiCondicion(elseIf);
        }
        else
        {
            getAnteriorToken();

            struct Else *sinoRep = inicializarSino();
            sentIf->sino.final = sinoRep;

            sinoRep->sino = token;
            match("Sino");

            struct BloqueCodigo *bloque2 = inicializarBloqueCodigo();
            sinoRep->contenido = bloque2;

            bloque_codigo(bloque2);
        }
    }
}

void sentenciaSi(struct SentenciaIf *sentIf)
{
    sentIf->nombre = token;
    match("Si");
    sentenciaSiCondicion(sentIf);
}