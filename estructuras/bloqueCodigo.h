void bloque_codigo(struct BloqueCodigo *bloque)
{

    bloque->llaveAbre = token;
    match("{");

    struct Sentencia *sent = inicializarSentencia();
    bloque->siguiente = sent;
    lista_sentencias(sent);

    bloque->llaveCierra = token;
    match("}");
}