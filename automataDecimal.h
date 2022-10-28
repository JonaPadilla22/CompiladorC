#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int IsNumberDecimal(char* str)
{
    int estado = 1;
    char *simbolos = "+-";
    int numc = 0;
    char car = str[numc];

    while (estado != 6 && estado !=0)
    {
        car = str[numc];
        numc++;

        switch (estado)
        {
        case 0:
            break;
        case 1:
            if (isdigit(car) == 1)
            {
                estado = 3;
            }
            else if (car == '+' || car == '-')
            {
                estado = 2;
            }
            else
            {
                estado = 0;
            }
            break;
        case 2:
            if (isdigit(car) == 1)
            {
                estado = 3;
                break;
            }
            estado = 0;
            break;
        case 3:
            if (isdigit(car) == 1)
            {
                continue;
            }
            else if ('.' == car)
            {
                estado = 4;
            }
            else
            {
                estado = 0;
            }
            break;
        case 4:
            if (isdigit(car) == 1)
            {
                estado = 5;
            }else {
                estado = 0;
            }
            break;
        case 5:
            if(isdigit(car) == 1){
                estado = 5;
            }else if(car == '\0'){
                estado = 6;
            }else{
                estado = 0;
            }
            break;
        }
    }

    return estado != 0 ? 1 : 0;
}
