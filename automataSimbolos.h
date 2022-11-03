#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int isSimbolToken(char* str)
{
    int estado = 1;
    char *simbolosGenerales = "*:;$),({}[]\\";
    char *simbolosLogicos = "<>!=";
    char suma = '+';
    char resta = '-';
    char division = '/';
    int numc = 0;
    char car = str[numc];
    while (estado != 9 && estado != 0)
    {
        switch (estado)
        {
        case 0:
            break;
        case 1:
            if (strchr(simbolosLogicos, car) != '\0')
            {
                estado = 2;
            }
            else if (strchr(simbolosGenerales, car) != '\0')
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

            if (car == '\0')
            {
                estado = 9;
                break;
            }
            if(car == '='){

                estado = 3;
                break;
            }
            estado = 0;
            break;
        case 3:
            if (car != '\0')
            {
                estado = 0;
                break;
            }
            estado = 9;
            break;
        case 4:
            if (car != '\0')
            {
                estado = 0;
                break;
            }
            estado = 9;
            break;
        case 5:
            if (car == '\0')
            {
                estado = 9;
                break;
            }
            if(car == '+'){
                estado = 7;
                break;
            }
            estado = 0;
            break;
        case 6:
            if (car == '\0')
            {
                estado = 9;
                break;
            }
            if(car == '-'){
                estado = 8;
                break;
            }
            estado = 0;
            break;
        case 7:
            if (car != '\0')
            {
                estado = 0;
                break;
            }
            estado = 9;
            break;
        case 8:
            if (car != '\0')
            {
                estado = 0;
                break;
            }
            estado = 9;
            break;
        }
        numc++;
        car = str[numc];
    }
    return (estado != 0) && (estado == 9) ? 1 : 0;
}
