void tipoDato(struct Asignacion *asignacion)
{
    auxT = getInfoToken();
    tokAux = tokAct;
    int x = 0;
    if (strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0)
    {
        struct Cadena *cad = inicializarCadena();
        asignacion->dato.cadena = cad;
        cad->cadena = token;
        cadena(cad);
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
            strcmp("!=", token.Lexema) == 0 ||
            strcmp("Verdadero", token.Lexema) == 0 ||
            strcmp("Falso", token.Lexema) == 0)
        {
            x = 1;
            break;
        }
    }

    token = auxT;
    tokAct = tokAux;

    if (x == 1)
    {
        struct Logico *logic = inicializarLogico();
        asignacion->dato.logico = logic;
        logico(logic);
        return;
    }
    else
    {
        struct Entero *ent = inicializarEntero();
        asignacion->dato.entero = ent;
        entero(ent);
        return;
    }

    printf("error en la linea %d columna %d, se esperaba TIPO DATO\n", token.NumLinea, token.NumCol);
}