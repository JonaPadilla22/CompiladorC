int logico(struct Logico *log)
{
    if (strcmp("(", token.Lexema) == 0)
    {
        log->parentesisAbre = token;
        match("(");
        struct Logico *logNuevo = inicializarLogico();
        log->sigDato.logico = logNuevo;
        logico(logNuevo);
        log->parentesisCierra = token;
        match(")");
    }

    if (strcmp("Verdadero", token.Lexema) == 0)
    {
        log->valor = token;
        match("Verdadero");
        return 1;
    }

    if (strcmp("Falso", token.Lexema) == 0)
    {
        log->valor = token;
        match("Falso");
        return 1;
    }

    if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0 || strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0 || strcmp("NUMERO", tipoTokenNames[token.Tipo]) == 0)
    {
        sigtok = getInfoSigToken();
        if (strcmp(">", sigtok.Lexema) == 0 || strcmp("<", sigtok.Lexema) == 0 || strcmp("==", sigtok.Lexema) == 0 || strcmp(">=", sigtok.Lexema) == 0 || strcmp("<=", sigtok.Lexema) == 0 || strcmp("!=", sigtok.Lexema) == 0)
        {
            log->valor = token;
            match(token.Lexema);
            log->operacion = token;
            operacionLogica();
            struct Logico *logNuevo = inicializarLogico();
            log->sigDato.logico = logNuevo;
            logico(logNuevo);
        }
        else if (strcmp("+", sigtok.Lexema) == 0 || strcmp("-", sigtok.Lexema) == 0 || strcmp("*", sigtok.Lexema) == 0 || strcmp("/", sigtok.Lexema) == 0)
        {
            log->valor = token;
            match(token.Lexema);
            log->operacion = token;
            operacionAritmetica();
            struct Entero *ent = inicializarEntero();
            log->sigDato.entero = ent;
            entero(ent);
        }
        else
        {
            log->valor = token;
            match(token.Lexema);
        }
        return 1;
    }

    if (strcmp(">", token.Lexema) == 0 || strcmp("<", token.Lexema) == 0 || strcmp("==", token.Lexema) == 0 || strcmp(">=", token.Lexema) == 0 || strcmp("<=", token.Lexema) == 0 || strcmp("!=", token.Lexema) == 0)
    {
        log->operacion = token;
        match(token.Lexema);
        struct Logico *logNuevo2 = inicializarLogico();
        log->sigDato.logico = logNuevo2;
        logico(logNuevo2);
        return 1;
    }

    if (strcmp("&&", token.Lexema) == 0 || strcmp("||", token.Lexema) == 0)
    {
        log->operacion = token;
        match(token.Lexema);
        return 1;
    }

    printf("error en la linea %d columna %d, se esperaba VALOR LOGICO\n", token.NumLinea, token.NumCol);
    return 0;
}
