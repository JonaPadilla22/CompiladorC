int comprobar_final_declaracion(struct Asignacion *asg)
{
    asg->identificador = token;
    matchTipoToken("ID");
    if (strcmp(";", token.Lexema) == 0)
        return 1;
    asg->igual = token;
    match("=");
    return 0;
}

void declaracion(struct Declaracion *dec)
{
    // CONSTANTE?
    if (strcmp("Nomoverle", token.Lexema) == 0)
    {
        dec->nomov = token;
        match("Nomoverle");
    }

    // ENTERO
    if (strcmp("Entero", token.Lexema) == 0)
    {
        dec->Tipo = Entero;
        match("Entero");
        struct Asignacion *asg = inicializarAsignacion();
        dec->asignacion = asg;
        if (comprobar_final_declaracion(asg) == 1)
        {
            dec->puntoComa = token;
            match(";");
            return;
        }

        struct Entero *ent = inicializarEntero();
        asg->dato.entero = ent;
        entero(ent);
        dec->puntoComa = token;
        match(";");
        return;
    }

    // DECIMAL
    if (strcmp("Decimal", token.Lexema) == 0)
    {
        dec->Tipo = Decimal;
        match("Decimal");
        struct Asignacion *asg = inicializarAsignacion();
        dec->asignacion = asg;
        if (comprobar_final_declaracion(asg) == 1)
        {
            dec->puntoComa = token;
            match(";");
            return;
        }
        struct Decimal *decim = inicializarDecimal();
        asg->dato.decimal = decim;
        decimal(decim);
        dec->puntoComa = token;
        match(";");
        return;
    }

    // CADENA
    if (strcmp("Cadena", token.Lexema) == 0)
    {
        dec->Tipo = Cadena;
        match("Cadena");
        struct Asignacion *asg = inicializarAsignacion();
        dec->asignacion = asg;
        if (comprobar_final_declaracion(asg) == 1)
        {
            dec->puntoComa = token;
            match(";");
            return;
        }
        struct Cadena *cad = inicializarCadena();
        asg->dato.cadena = cad;

        cadena(cad);
        dec->puntoComa = token;
        match(";");
        return;
    }

    // LOGICO
    if (strcmp("Logico", token.Lexema) == 0)
    {
        dec->Tipo = Logico;
        match("Logico");
        struct Asignacion *asg = inicializarAsignacion();
        dec->asignacion = asg;
        if (comprobar_final_declaracion(asg) == 1)
        {
            dec->puntoComa = token;
            match(";");
            return;
        }
        struct Logico *log = inicializarLogico();
        asg->dato.logico = log;

        logico(log);
        dec->puntoComa = token;
        match(";");
        return;
    }
}