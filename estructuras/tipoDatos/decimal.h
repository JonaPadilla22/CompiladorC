int decimal(struct Decimal *dec)
{
    if (strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            dec->valor = token;
            matchTipoToken("NUMERO");
            dec->opAritmetica = token;
            operacionAritmetica();
            struct Decimal *decimalNuevo = inicializarDecimal();
            dec->sigDecimal = decimalNuevo;
            decimal(decimalNuevo);
        }
        else
        {
            dec->valor = token;
            matchTipoToken("NUMERO");
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            dec->valor = token;
            matchTipoToken("ID");
            dec->opAritmetica = token;
            operacionAritmetica();
            struct Decimal *decimalNuevo = inicializarDecimal();
            dec->sigDecimal = decimalNuevo;
            decimal(decimalNuevo);
        }
        else
        {
            dec->valor = token;
            matchTipoToken("ID");
        }
    }
    else if (strcmp("(", token.Lexema) == 0)
    {
        dec->parentesisAbre = token;
        match("(");
        struct Decimal *decimalNuevo1 = inicializarDecimal();
        dec->sigDecimal = decimalNuevo1;
        decimal(decimalNuevo1);
        dec->parentesisCierra = token;
        match(")");
        sigtok = getInfoToken();
        if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            dec->opAritmetica = token;
            operacionAritmetica();
            struct Decimal *decimalNuevo2 = inicializarDecimal();
            dec->sigDecimal = decimalNuevo2;
            decimal(decimalNuevo2);
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba DECIMAL\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}
