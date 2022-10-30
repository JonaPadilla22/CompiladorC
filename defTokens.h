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

struct Token getInfoToken(){
    struct Token tok;
    tok = tokAct->info;
    return tok;
};

struct Token getInfoSigToken(){
    struct Token tok;
    struct nodo *sigTok;
    sigTok = tokAct->der;
    tok = sigTok->info;
    return tok;
};

static void getToken(){
    tokAct=tokAct->der;
    if(tokAct==NULL && strcmp("}", token.Lexema)!=0){
        printf("error en la linea %d columna %d, se esperaba simbolo }\n", token.NumLinea, token.NumCol);
        return;
    }else if(tokAct==NULL && strcmp("}", token.Lexema)==0){
        return;
    }
    token = getInfoToken();
}

void getAnteriorToken(){
    tokAct=tokAct->izq;
    token = getInfoToken();
}


