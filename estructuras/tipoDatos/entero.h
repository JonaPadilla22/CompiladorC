int entero(struct Entero *ent)
{
    if (strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            ent->valor = token;
            matchTipoToken("NUMERO");
            ent->opAritmetica = token;
            operacionAritmetica();
            struct Entero *integer = inicializarEntero();
            ent->sigEntero = integer;
            entero(integer);
        }
        else
        {
            ent->valor = token;
            matchTipoToken("NUMERO");
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            ent->valor = token;
            matchTipoToken("ID");
            ent->opAritmetica = token;
            operacionAritmetica();
            struct Entero *integer = inicializarEntero();
            ent->sigEntero = integer;
            entero(integer);
        }
        else
        {
            matchTipoToken("ID");
        }
    }
    else if (strcmp("(", token.Lexema) == 0)
    {
        ent->parentesisAbre = token;
        match("(");
        struct Entero *integer1 = inicializarEntero();
        ent->sigEntero = integer1;
        entero(integer1);
        ent->parentesisCierra = token;
        match(")");
        sigtok = getInfoToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            ent->opAritmetica = token;
            operacionAritmetica();
            struct Entero *integer2 = inicializarEntero();
            entero(integer2);
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba ENTERO\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}
