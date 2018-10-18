%{
/*Detecta e imprime los números enteros*/
#include <stdio.h>
int c_int = 0, c_short = 0,c_ident = 0,c_const = 0,c_operador = 0, c_car_puntuacion=0;
%}
%option noyywrap
DIGITO [0-9]
LETRA [a-zA-Z]
%%
int {c_int++;}
short {c_short++;}
{DIGITO}+	{c_const++; }
{LETRA}+{DIGITO}*	{c_ident++; }
[+-/=]	{c_operador++; }
[{}();]	{c_car_puntuacion++; }
.|\n		;
%% 
int main(void) {
	yylex();
	printf("Se reconocieron. \n");
	printf("%d Palabras reservadas tipo int . \n",c_int);
	printf("%d Palabras reservadas tipo short . \n\n", c_short);
	printf("%d Identificadores. \n",c_ident);
	printf("%d Constantes . \n\n", c_const);
	printf("%d Operadores .\n\n", c_operador);
	printf("%d Caracteres de puntuacion. \n\n", c_car_puntuacion);
	return 0;
}


