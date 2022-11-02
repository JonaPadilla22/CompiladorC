
const char* tipoTokenNames[] = {"PALABRA RESERVADA", "ID", "NUMERO", "SIMBOLO", "CADENA"};

enum TipoToken{
    PalRes,
    id,
    num,
    sim,
    cad
};

typedef struct{
    enum TipoToken Tipo;
    char *Lexema;
    int Valor;
    int NumLinea;
    int NumCol;
} Token;

struct nodo{
    Token info;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *tokAct;
Token token;

Token getInfoToken(){
    Token tok;
    tok = tokAct->info;
    return tok;
};

Token getInfoSigToken(){
    Token tok;
    struct nodo *sigTok;
    sigTok = tokAct->der;
    tok = sigTok->info;
    return tok;
};

static void getToken(){
    if(tokAct->der==NULL){
        token.Lexema = "";
        return;
    }
    tokAct=tokAct->der;
    token = getInfoToken();
}

void getAnteriorToken(){
    tokAct=tokAct->izq;
    token = getInfoToken();
}


