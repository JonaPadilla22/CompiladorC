
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

int isEntero(char* str){
    int estado = 1;
    int numc = 0;
    char c = str[numc];

    while (estado == 1 || estado == 2 || estado == 3){
          switch (estado) {
            case 1:
                if(isdigit(c)!=0){
                    estado = 3;
                }else if(c == '+' || c == '-'){
                    estado = 2;
                }else{
                    estado = 0;
                    break;
                }
                numc++;
                c = str[numc];
              break;
            case 2:
                if(isdigit(c)!=0){
                    estado = 3;
                }else{
                    estado = 0;
                    break;
                }
                numc++;
                c = str[numc];
              break;
            case 3:
                if(isdigit(c)!=0){
                    estado = 3;
                }else if (c == '\0'){
                    estado = 4;
                    break;
                }
                else{
                    estado = 0;
                    break;
                }
                numc++;
                c = str[numc];
              break;
        }

    }

    if(estado == 4){
        return 1;
    }else{
        return 0;
    }
}

