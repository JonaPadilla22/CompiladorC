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



