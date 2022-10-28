#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int isCadena(FILE *file)
{
    int estado = 1;
    char car;

    while (estado != 3 && estado !=0)
    {

        switch (estado){
            case 0:
                printf("Error \n");
                int posicion = ftell(file);
                fseek(file, posicion-1, SEEK_SET);
                break;
            case 1:
                if (car == '"' || car == '\'')
                {
                    estado = 2;
                }else{
                    estado = 0;
                }
                break;
            case 2:
                if (car == '"' || car == '\'')
                {
                    estado = 3;
                }

                if( car == EOF || car == '\n')
                {
                    estado = 0;
                }
                break;
        }

        car = (char)fgetc(file);
    }
    return estado == 3 ? 1 : 0;
}

