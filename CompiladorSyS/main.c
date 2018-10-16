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


typedef enum {
	LLAVE_IZQ,LLAVE_DER,ID,CONSTANTE,PAREN_IZQ,PAREN_DER,PUNTO_Y_COMA,
	ASIGNACION,SUMA,INT,SHORT,RESTA,MULTIPLICACION,FDT,ERROR_L
}TOKEN;

TOKEN machScanner(int ESTADO);
TOKEN esReservada();
void agregarC (int c);

typedef struct {
	char contenido[50];
	char atributo[50];
} simbolo;

simbolo TABLA_S[100] ;

char numeros[] = "1234567890";
char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char otro[] = "!@#~$%^&_`/.,][?";
char sp[] = {'\n',' ','\t'};



char BUFFER [50]={};
int indexBUFFER = 0;
char CARACTER;

char RESERVADA_INT[] = "int";
char RESERVADA_SHORT[] = "short";

char *escanner_C [] = {letras,numeros,"+","-","(",")","{","}",";","*","=","\f",sp,otro};
int escanner_EF[] = {2,4,5,6,7,8,9,10,11,12,13,15,16};
int escanner_TT[16][14] = {{1,3,5,6,7,8,9,10,11,12,13,15,0,14},
							{1,1,2,2,2,2,2,2,2,2,2,2,2,2},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,3,4,4,4,4,4,4,4,4,4,4,4,4},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14},
							{14,14,14,14,14,14,14,14,14,14,14,14,14,14}};



int getToken(char cadena[]);
void scanner (char cadena[]);
void almacenarEnTS(char atributo[]);
void copy(char *dest,char *desde);
void errorLexico();
TOKEN proximoToken();
void unGet();
int INDEX = 0;
TOKEN TOKEN_ULTIMO;
int TOKEN_TOMADO=0;
FILE *archivoTxt;


int main(int argc, char *argv[]) {
    
    
    printf("El compilador , comprobara el archivo programa 'programa.txt' . \n");
    
    char nombre[15]="programa.txt";
    
    int i;
    
    archivoTxt = fopen( nombre, "r" );
    printf( "Archivo: %s -> ", nombre );
    if( archivoTxt!=NULL )
      printf( "Existe (ABIERTO)\n" );
    else
    {
      printf( "Error (NO ABIERTO)\n" );
      return 1;
    }
    
    Objetivo();
    /*
	i = 0;
	while(i<5){
		proximoToken();
		i++;
	}
	*/
    mostrarTS();
    
    printf("FINALIZADO");
    fclose(archivoTxt);
 
    return 0;
}



//SCANNER

TOKEN escannerAutomata(int *tT, int f, int c,char *lenguaje[],int estFinales[])
{
    int estado = 0;
    CARACTER = fgetc(archivoTxt);
    
    if(CARACTER=='\377')
			CARACTER = '\f';

    while(!esFinal(estado,estFinales,f)){	    
        int columnaE = posEntrada(CARACTER,lenguaje,c);
        if(columnaE==-1){break;}
        
        int estadoNuevo = obtenerTran(estado,columnaE,f,c,tT);
        if(estadoNuevo == -1){break;}
        
        estado = estadoNuevo;
        if(estadoNuevo == 1 || estadoNuevo == 3){
        	agregarC(CARACTER);
		}
		
		if(estado == 14)
			return machScanner(14);
	    
		if(!esFinal(estado,estFinales,f) )
			CARACTER = fgetc(archivoTxt);
			    
		if(CARACTER=='\377')
			CARACTER = '\f';				    
    }
    	    
	return machScanner(estado);
	
}

TOKEN machScanner(int ESTADO){
	//	LLAVE_IZQ,LLAVE_DER,ID,CONSTANTE,PAREN_IZQ,PAREN_DER,PUNTO_Y_COMA,
	//	ASIGNACION,SUMA,INT,SHORT,RESTA,MULTIPLICACION,FDT
	switch (ESTADO){
		case 2:
			unGet();	
			return esReservada();									
      	break;
      	case 4:
      		unGet();
      		almacenarEnTS("constante");
      		printf( " %s ","CONSTANTE");
      		return CONSTANTE;
      	break;
		case 14:			
			//errorLexico();
			return ERROR_L;
		break;
		case 5:
			printf( " %s ","SUMA");
			return SUMA;
		break;
		case 6:
			printf( " %s ","RESTA");
			return RESTA;			
		case 7:
			printf( " %s ","PAREN_IZQ");
			return PAREN_IZQ;
		break;
		case 8:
			printf( " %s ","PAREN_DER");
			return PAREN_DER;
		break;
		case 9:
			printf( " %s ","LLAVE_IZQ");
			return LLAVE_IZQ;
		break;
		case 10:
			printf( " %s ","LLAVE_DER");
			return LLAVE_DER;
		break;
		case 11:
			printf( " %s ","PUNTO_Y_COMA \n");
			return PUNTO_Y_COMA;
		break;
		case 12:
			printf( " %s ","MULTIPLICACION");
			return MULTIPLICACION;
		break;
		case 13:
			printf( " %s ","ASIGNACION");
			return ASIGNACION;
		break;
		case 15:
			printf( " %s ","FDT");
			return FDT;
		break;
	}
	return FDT;
}

void unGet(){
	ungetc(CARACTER,archivoTxt)	;
}

TOKEN esReservada(){

	if(equal(&BUFFER[0],&RESERVADA_INT[0])){
		printf( " %s ","INT");
		limpiarBuffer();
		return INT;
	}
		
		
	if(equal(&BUFFER[0],&RESERVADA_SHORT[0])){
		printf( " %s ","SHORT");
		limpiarBuffer();
		return SHORT;	
	}
		
	printf( " %s ","ID");
	if(existeEnTS())
		return ID;
		
	almacenarEnTS("id");	
	return ID;	
	
}

int equal(char *aEsta,char *esta){
int i = 0;
	while(esta[i]!='\0'){
		if(esta[i] != aEsta[i])
			return 0;
		i++;		
	}
	return 1;
}

void agregarC (int c){
	BUFFER[indexBUFFER] = c;
	indexBUFFER=indexBUFFER+1;
}



int sizeTS(){
	int i = 0 ; 
	while(TABLA_S[i].contenido[0]!='\0'){		
		i++;
	}
	return i;
}

void almacenarEnTS(char atributo[]){
	int size = sizeTS();	
	copy(&TABLA_S[size].contenido[0],&BUFFER[0]);
	copy(&TABLA_S[size].atributo[0],&atributo[0]);	
	limpiarBuffer();
}

void copy(char *dest,char *desde){
	int i = 0;
	while(desde[i]!='\0'){
		dest[i] = desde[i];
		i++;
	}
}

void limpiarBuffer(){
	int i = 0;
	while(BUFFER[i]!='\0'){
		BUFFER[i] = '\0';
		i++;
	}
	indexBUFFER=0;
}

int existeEnTS(){
	int j=0;
	int i = 0;
	while (j < sizeTS()) {
		for( i ; i < 50 ; i++){
			if(TABLA_S[j].contenido[i] != BUFFER[i])
				break;
			if(i==49)
				return 1;
		}
		
	i=0;	
	j++;
	}
	
	return 0;
}

void mostrarTS(){
	int size = sizeTS();
	for(size; size >= 0 ; size--){
		printf(" %s  %s  \n",TABLA_S[size].atributo,TABLA_S[size].contenido);
	}
}



// PARSER

void Objetivo(void){
	Programa();
	Match(FDT);
}

void Programa(void){
	Match(LLAVE_IZQ);
	ListaSentencias();
	Match(LLAVE_DER);
}

void ListaSentencias(void){
	Linea(); //Primer Linea de sentencia
	
	while(1){
		switch (proximoToken()){
		case INT:
		case ID:
		case SHORT:
			Linea();
		break;
		default:
			return;					
		}		 
	}
	
}

void Linea(void){
	TOKEN token = proximoToken();
	
	switch (token){
		case INT: //INT ID ASIGNACION <Valor>  PUNTOYCOMA
			Match(INT); Match(ID); Match(ASIGNACION); 	Valor(); Match(PUNTO_Y_COMA);
			break;
		case ID:  // ID ASIGNACION  <Valor>  PUNTOYCOMA
			Match(ID);  Match(ASIGNACION); 	Valor();  Match(PUNTO_Y_COMA);
			break;
		case SHORT: // SHORT ID ASIGNACION <Valor>  PUNTOYCOMA
			Match(SHORT); Match(ID); Match(ASIGNACION); 	Valor(); Match(PUNTO_Y_COMA);
			break;
		default:
			ErrorSintactico(token); 
		break;
	}
}

void Valor (void) {
	//<Valor> 	-> <Primaria> { <Operador> <Primaria> }
	TOKEN t;
	Primaria();	
	for(t=proximoToken(); t==SUMA||t==RESTA|| t==MULTIPLICACION; t= proximoToken()){
		Operador();
		Primaria();
	}
}

void Operador(void){
	// <operador> -> uno de SUMA RESTA MULTIPLICACION
	TOKEN t = proximoToken();
	if(t==SUMA||t==RESTA|| t==MULTIPLICACION){
		Match(t);
	}else{
		ErrorSintactico();	
	}
}

void Primaria(void){
	TOKEN t = proximoToken();
	if(t == ID || t==CONSTANTE){
		Match(t);
	}else{
		ErrorSintactico();
	}
}

void ErrorSintactico(TOKEN t){
	printf( " %s ","* ERROR_SINTACTICO");
	
}

void errorLexico(){
	printf( " %s ","* ERROR_LEXICO");

}


TOKEN proximoToken(){
	if(!TOKEN_TOMADO){
		TOKEN_ULTIMO =  escannerAutomata(&escanner_TT[0][0],16,14,escanner_C,escanner_EF);
		if(TOKEN_ULTIMO == ERROR_L){
			errorLexico();
			char ch = getchar();
		} 
		TOKEN_TOMADO = 1 ;
	}
    	
    return TOKEN_ULTIMO;
}

void Match(TOKEN token){
	if ( !(token == proximoToken())){
		 ErrorSintactico(token);  
		 char ch = getchar();
	}
	
		 
	TOKEN_TOMADO = 0;
}







