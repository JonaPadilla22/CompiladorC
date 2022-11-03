int cadena(struct Cadena *caddPr)
{
    if (strcmp("CADENA", tipoTokenNames[token.Tipo]) == 0)
    {
        caddPr->cadena = token;
        matchTipoToken("CADENA");
        if (strcmp(",", token.Lexema) == 0)
        {
            caddPr->coma = token;
            match(",");
            struct Cadena *cad = inicializarCadena();
            caddPr->sigCadena = cad;
            cadena(cad);
        }
    }
    else if (strcmp("ID", tipoTokenNames[token.Tipo]) == 0)
    {
        caddPr->cadena = token;
        matchTipoToken("ID");
        if (strcmp(",", token.Lexema) == 0)
        {
            caddPr->coma = token;
            match(",");
            struct Cadena *cad = inicializarCadena();
            caddPr->sigCadena = cad;
            cadena(cad);
        }
    }
    else
    {
        printf("error en la linea %d columna %d, se esperaba CADENA\n", token.NumLinea, token.NumCol);
        return 0;
    }
    return 1;
}
