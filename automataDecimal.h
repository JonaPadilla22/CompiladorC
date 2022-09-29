#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int IsNumberDecimal(FILE *file)
{

    int estado = 1;
    char *simbolos = "+-";
    char car;

    while (estado != 5 && estado !=0)
    {
        car = fgetc(file);

        switch (estado)
        {
        case 0:
            printf("Error \n");
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
                continue;
            }
            else estado = 5;
        }
    }

    return estado != 0 ? 1 : 0;
}
