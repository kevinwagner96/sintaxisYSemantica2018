//
//  automata.h
//  CompiladorSyS
//
//  Created by Kevin Wagner on 20/9/18.
//  Copyright © 2018 Kevin Wagner. All rights reserved.
//

#ifndef automata_h
#define automata_h

#include <stdio.h>

int pertenece (char letra, char vect []);

int automata(int *tT, int f, int c,char *lenguaje[],int estFinales[],char cadena[],char *Bf);
int posEntrada (char caracter , char *lenguaje[] , int size);
int obtenerTran(int posF,int posC,int sizeF,int sizeC, int *tT);
int esFinal(int estado , int estadosF[], int sizeF);


#endif
// /* automata_h *
