const char* tipoTokenNames[] = {"PALABRA RESERVADA", "ID", "NUMERO", "SIMBOLO", "CADENA"};

enum TipoToken{
    PalRes,
    id,
    num,
    sim,
    cad
};

struct Token{
    enum TipoToken Tipo;
    char *Lexema;
    int Valor;
    int NumLinea;
    int NumCol;
};

struct nodo{
    struct Token info;
    struct nodo *izq;
    struct nodo *der;
};
