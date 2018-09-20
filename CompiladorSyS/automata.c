//
//  automata.c
//  CompiladorSyS
//
//  Created by Kevin Wagner on 20/9/18.
//  Copyright © 2018 Kevin Wagner. All rights reserved.
//

#include "automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int automata(int *tT, int f, int c,char *lenguaje[],int estFinales[],char cadena[])
{
    int estado = 0;
    int i;
    for(i=0; cadena[i] ; i++){
        
        int columnaE = posEntrada(cadena[i],lenguaje,c);
        if(columnaE==-1){break;}
        
        int estadoNuevo = obtenerTran(estado,columnaE,f,c,tT);
        if(estadoNuevo == -1){break;}
        
        estado = estadoNuevo;
    }
    
    if((i)==strlen(cadena) && esFinal(estado,estFinales,f)){
        return 1;
    }
    
    return 0;
}


int pertenece (char letra, char *vect){
    char i=0;
    for(i=0 ; vect[i] ; i++){
        if(letra == vect[i]){
            return  1;
        }
    }
    return 0;
}

int posEntrada (char caracter , char *lenguaje[] , int size){
    int i = 0;
    for(i;i<size;i++){
        if(pertenece(caracter,lenguaje[i])){
            return i;
        }
    }
    return -1;
}

int obtenerTran(int posF,int posC,int sizeF,int sizeC, int *tT){
    return tT[((posF*sizeC)+posC)];
}

int esFinal(int estado , int estadosF[], int sizeF){
    int i = 0;
    for(i ; i < sizeF ; i++){
        if(estado == estadosF[i]){
            return 1;
        }
    }
    return 0;
}
