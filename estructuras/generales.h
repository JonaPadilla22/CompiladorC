#include "tipoDatos/entero.h"
#include "tipoDatos/decimal.h"
#include "tipoDatos/cadena.h"
#include "tipoDatos/logico.h"
#include "tipoDatos/tipoDato.h"

void asignacion()
{
    struct Asignacion *asign = inicializarAsignacion();
    asign -> identificador = token;
    matchTipoToken("ID");
    asign -> igual = token;
    match("=");
    tipoDato(asign);
    asign -> puntoComa = token;
    match(";");
}



