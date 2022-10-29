struct Token token;
struct nodo *tokAct;

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

struct Token getInfoToken(struct nodo *act){
    struct Token tok;
    tok = act->info;
    return tok;
};

static void getToken(){
    tokAct=tokAct->der;
    token = getInfoToken(tokAct);
}

void getAnteriorToken(){
    tokAct=tokAct->izq;
    token = getInfoToken(tokAct);
}


