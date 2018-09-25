//
//  main.c
//  CompiladorSyS
//
//  Created by Kevin Wagner on 20/9/18.
//  Copyright © 2018 Kevin Wagner. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "automata.h"

char numeros[] = "1234567890";
char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char otro[] = "!@#~$%^&_`/.,][?";
char fdt[] = {'\n'};
char sp[] = {'\n',' ','\t'};
char sigPunt[] = "(){};";
char operadores[] = "+-*=";

char BUFFER [100]={};
int indexBUFFER = 0;

char *identiC [] = {letras,numeros}; // en orden
int identiEF [] = {1,2};
int identiTT [3][2]={{ 1,-1},
    { 1, 2},
    {-1, 2}};


char *palabraR_C [] = {"i","n","t","s","h","o","r"};
int palabraR_EF []  =  {3};
int palabraR_TT [8][7]={{ 1,-1,-1, 4,-1,-1,-1},
    {-1, 2,-1,-1,-1,-1,-1},
    {-1,-1, 3,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1, 5,-1,-1},
    {-1,-1,-1,-1,-1, 6,-1},
    {-1,-1,-1,-1,-1,-1, 7},
    {-1,-1, 3,-1,-1,-1,-1}};


char *constantes_C [] = {numeros};
int constantes_EF []  =  {1};
int constantes_TT [2][1]= {{1},{1}};

char *operadores_C [] = {"+","-","*","="};
int operadores_EF []  =  {1};
int operadores_TT [2][4]= {{ 1, 1, 1, 1},
    {-1,-1,-1,-1}};

char *sigPunt_C [] = {"(",")","{","}",";"};
int sigPunt_EF []  =  {1};
int sigPunt_TT [2][5]= {{ 1, 1, 1, 1, 1},
    {-1,-1,-1,-1,-1}};


char *escanner_C[] = {letras,numeros,"+","-","*","=","(",")",";",fdt," ",otro};
int escanner_EF[] = {2,4,5,6,7,8,9,10,11,12};
int escanner_TT[14][12] = {{1,3,5,6,7,8,9,10,11,12,0,13},
						  {1,1,2,2,2,2,2,2,2,2,2,2},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {4,3,4,4,4,4,4,4,4,4,4,4},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13},
						  {13,13,13,13,13,13,13,13,13,13,13,13}};

int getToken(char cadena[]);

int main(int argc, char *argv[]) {
    
    
    printf("Ingrese una cadena para verificar su categoria lexica . \n");
    char cadena[100];
    scanf("%s", cadena );
    
    
    //printf("Pertenece a la categoria %d ",getToken(cadena));
    scanner(cadena);
    
    scanf("%s", cadena );
    
    
    return 0;
}

void scanner (char cadena[]){
	
    printf("TT = %d",escannerAutomata(&escanner_TT[0][0],14,12,escanner_C,escanner_EF,cadena,&BUFFER))  ;
    printf("Buffer = %s",BUFFER)  ;
	     
}

int escannerAutomata(int *tT, int f, int c,char *lenguaje[],int estFinales[],char cadena[])
{
    int estado = 0;
    int i;
    for(i=0; cadena[i] ; i++){
        
        int columnaE = posEntrada(cadena[i],lenguaje,c);
        if(columnaE==-1){break;}
        
        int estadoNuevo = obtenerTran(estado,columnaE,f,c,tT);
        if(estadoNuevo == -1){break;}
        
        estado = estadoNuevo;
        if(estadoNuevo == 1 || estadoNuevo == 3){
        	agregarC(cadena[i]);
		}
    }
    
    if((i)==strlen(cadena) /*&& esFinal(estado,estFinales,f)*/){
        return estado;
    }
    
    return 0;
}

void agregarC (int c){
	BUFFER[indexBUFFER] = c;
	indexBUFFER=indexBUFFER+1;
}
/*
int getToken(char cadena[]){
  
    if(automata(&identiTT[0][0],3,2, identiC,identiEF,cadena))
       return 1;
    
    if(automata(&palabraR_TT[0][0],8,7, palabraR_C,palabraR_EF,cadena))
        return 2;
    
    if(automata(&constantes_TT[0][0],2,1, constantes_C,constantes_EF,cadena))
        return 3;
    
    if(automata(&operadores_TT[0][0],2,4, operadores_C,operadores_EF,cadena))
        return 4;
    
    if(automata(&sigPunt_TT[0][0],2,5, sigPunt_C,sigPunt_EF,cadena))
        return 5;
    
    return 0;
}
*/
