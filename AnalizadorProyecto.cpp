/*
	Jenny
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

int esSepCadena(string palabra);
int esSepDigito(string palabra);
int esSepOprComparacion(string palabra);
int esSepFuncionesMat(string palabra);
int esSepParentesCerr(string palabra);
int esSepDelimitadors(string palabra);

int esOperadorComp(string palabra);
int esOperadorArit(string palabra);
int esPalabraReser(string palabra);
int esDelimitadors(string palabra);
int esSaltosDLinea(string palabra);

/*										SEPARADORES (editando)									*/
string sepCadenas [] = {" ",";", ":", "/", "*", "+", "-", "<", ">", "!", "="}; //separador para cadenas
string sepDigitos [] = {" ", ")", "=", "/", "*", "+", "-", "<", ">", "!"}; //separador para digitos
string sepOprComp [] = {" ", "("}; //separador para Operaciones de comparacion
string sepFuncMat [] = {" ", "("}; //separador para funciones matematicas
string sepPareCer [] = {" ", "<", ">", "!", "+", "-", "/", "*"};//separador para parentesis cerrado
string sepDelimta [] = {" ", "\t", "\n"};

/*												TOKENS											*/
string operadorComparacio [] = {"<", ">", "!"};
string operadorAritmetico [] = {"+", "-", "/", "*"};
string palabrasReservadas [] = {"Inicio", "Fin", "mientras", "si", "contrario", "and", "or", "imprimir", "entero", 
								"bool", "cadena", "caracter", "dec", "igual"}; 
string delimitadores [] = {"{", "}", ";", ":"};//solo será usado en un salto de línea
string saltosdLin [] = {" ", "\n", "\t"};//para saltos de linea
char opAsignacin = '=';
char parenAbiert = '(';
char parenCerrad = ')';
char llaveCerrad = '}';
char comillas = '"';

FILE *archivo;
char caracter;	// Variable que almacenara el caracter leido

int cont=0;	// Contador de tokens

int main(){
	string contenido;
	string token;
	string concatenar = "";
	int estado;
	int contToken = 0;
		
	archivo=fopen("prueba.txt","r");
	if(archivo == NULL){
		printf("El archivo no existe");
		exit(0);
	}else{
		caracter = getc(archivo);	
		
		while(caracter != EOF){
			
			switch(estado){
				case 0:
					if(isalpha(caracter)){
						estado = 1;
					}else if(isdigit(caracter)){
						estado = 2;
					}else if(caracter == ','){
						estado = 3;
					}else if(esOperadorComp(&caracter) == 1){
						estado = 5;
					}else if(esOperadorArit(&caracter) == 1){
						estado = 6;
					}else if(caracter == opAsignacin){
						estado = 7;
					}else if(caracter == parenAbiert){
						estado = 8; 
					}else if(caracter == parenCerrad){
						estado = 9;
					}else if(esDelimitadors(&caracter) == 1){
						estado = 10;
					}else if(caracter == llaveCerrad){
						estado = 11;
					}else if(esSaltosDLinea(&caracter) == 1){
						estado = 0;
					}else if(caracter = comillas){
						estado = 0;
					}else{
						printf("Error Case 0\n");
					}
				break;
				
				case 1:
					if(isalpha(caracter)){
						estado = 1;
					}else if(isdigit(caracter)){
						estado = 1;
					}else if(esSepCadena(&caracter)==1){
						estado = 0;
					}
					else{
						printf("Error en el caso 1");
					}
				break;
			}
		}
	}
}

int esOperadorComp(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(operadorComparacio[i]) / sizeof(operadorComparacio[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((operadorComparacio[i].compare(letra)) == 0 ){
			return 1;
		}
	}
	return 0;
}

int esOperadorArit(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(operadorAritmetico[i]) / sizeof(operadorAritmetico[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((operadorAritmetico[i].compare(letra)) == 0 ){
			return 1;
		}
	}
	return 0;
}

int esPalabraReser(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(palabrasReservadas[i]) / sizeof(palabrasReservadas[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((palabrasReservadas[i].compare(letra)) == 0 ){
			return 1;
		}
	}
	return 0;
}

int esSaltosDLinea(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(saltosdLin[i]) / sizeof(saltosdLin[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((saltosdLin[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esDelimitadors(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(delimitadores[i]) / sizeof(delimitadores[0]);
	
	for(i = 0; i < asize ; i++){
		if((delimitadores[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepCadena(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepCadenas) / sizeof(sepCadenas[0]);
	
	for(i=0; i < asize; i++){
		if((sepCadenas[i].compare(letra))==0){
			return 1;
		}
	}
	return 0;
}

int esSepDigito(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepDigitos[i]) / sizeof(sepDigitos[0]);
	
	for(i = 0; i < asize ; i++){
		if((sepDigitos[i].compare(letra))==0){
			return 1;
		}
	}
	return 0;
}

int esSepOprComparacion(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepOprComp[i]) / sizeof(sepOprComp[0]);
	
	for(i = 0; i < asize ; i++){
		if((sepOprComp[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepFuncionesMat(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepFuncMat[i]) / sizeof(sepFuncMat[0]);

	for(i = 0; i < asize ; i++){
		if((sepFuncMat[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepParentesCerr(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepPareCer[i]) / sizeof(sepPareCer[0]);
	
	for( i = 0 ; i < asize ; i++){
		if((sepPareCer[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepDelimitadors(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepDelimta[i]) / sizeof(sepDelimta[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((sepDelimta[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}


