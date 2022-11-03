void sentencia(struct Sentencia *sent)
{
    // CONDICION
    if (strcmp("Si", token.Lexema) == 0)
    {

        struct SentenciaIf *sentIf = inicializarSentenciaSi();
        sent->sentencia.sentenciaIf = sentIf;
        sent->Tipo = SentenciaSi;

        sentenciaSi(sentIf);
        return;
    }

    // CICLO POR
    if (strcmp("Por", token.Lexema) == 0)
    {
        struct SentenciaPor *por = inicializarSentenciaPor();
        sent->sentencia.sentenciaPor = por;
        sentenciaPor(por);
        return;
    }

    // SALIDA
    if (strcmp("TintaFuera", token.Lexema) == 0)
    {
        struct Escribir *escrib = inicializarEscribir();
        sent->sentencia.escribir = escrib;
        escribir(escrib);
        return;
    }

    // ENTRADA
    if (strcmp("TintaDentro", token.Lexema) == 0)
    {
        struct Leer *lee = inicializarLeer();
        sent->sentencia.leer = lee;
        leer(lee);
        return;
    }

    // DECLARACION
    if (strcmp("Nomoverle", token.Lexema) == 0 ||
        strcmp("Entero", token.Lexema) == 0 ||
        strcmp("Cadena", token.Lexema) == 0 ||
        strcmp("Decimal", token.Lexema) == 0 ||
        strcmp("Logico", token.Lexema) == 0)
    {
        struct Declaracion *dec = inicializarDeclaracion();
        sent->sentencia.declaracion = dec;
        declaracion(dec);
        return;
    }

    // ASINGANCION
    getToken();

    if (strcmp("=", token.Lexema) == 0)
    {
        getAnteriorToken();
        struct Asignacion *asg = inicializarAsignacion();
        sent->sentencia.declaracion = asg;
        asignacion(asg);
        return;
    }

    printf("Error en la linea %d columna %d\n", token.NumLinea, token.NumCol);
}

void lista_sentencias(struct Sentencia *sent)
{
    while (strcmp("}", token.Lexema) != 0 && token.Lexema != "")
    {
        sentencia(sent);
        if (strcmp("}", token.Lexema) != 0 && token.Lexema != "")
        {
            struct Sentencia *sent = inicializarSentencia();
            sent->siguiente = sent;
        }
    }
}
