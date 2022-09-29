#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int IsSymbol(FILE *file)
{

    int estado = 1;
    char *simbolosGenerales = "*:;$)({}[]\\";
    char *simbolosLogicos = "<>!=";
    char suma = '+';
    char resta = '-';
    char division = '/';
    char car;

    while (estado != 7 && estado != 0)
    {
        car = fgetc(file);
        switch (estado)
        {
        case 0:
            printf("Error \n");
            break;
        case 1:
            // printf("Contains %s\n",strchr(simbolosLogicos, car ) != '\0' ? "si" : "no");
            if (strchr(simbolosLogicos, car) != '\0')
            {
                estado = 2;
            }
            else if (strchr(simbolosGenerales, car) != '\0')
            {
                estado = 7;
            }
            else if ('\\' == car)
            {
                estado = 3;
            }
            else if ('/' == car)
            {
                estado = 4;
            }
            else if ('+' == car)
            {
                estado = 5;
            }
            else if ('-' == car)
            {
                estado = 6;
            }
            break;
        case 2:
            if (car != '=' && car != '(')
            {
                estado = 0;
                break;
            }
            estado = 7;

            break;
        case 3:
            if (car != '\\')
            {
                estado = 0;
                break;
            }
            estado = 7;
            break;
        case 4:
            if ('/' == car)
            {
                estado = 0;
                break;
            }
            estado = 7;
            break;
        case 5:
            if ('+' == car)
            {
                estado = 0;
                break;
            }
            estado = 7;
            break;
        case 6:
            if ('-' == car)
            {
                estado = 0;
                break;
            }
            estado = 7;
            break;
        }
    }
    return (estado != 0) && (estado == 7) ? 1 : 0;
}
