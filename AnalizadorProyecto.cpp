/*
	Jenny
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int esSepCadena(string palabra);
int esSepDigito(string palabra);
int esSepOprComparacion(string palabra);
int esSepFuncionesMat(string palabra);
int esSepParentesAbier(string palabra);
int esSepParentesCerr(string palabra);
int esSepDelimitadors(string palabra);

int esOperadorComp(string palabra);
int esOperadorArit(string palabra);
int esPalabraReser(string palabra);
int esDelimitadors(string palabra);
int esSaltosDLinea(string palabra);

/*										SEPARADORES (editando)									*/
string sepCadenas [] = {" ",";", ":", "/", "*", "+", "-", "<", ">", "!", "=", "(", "\""}; //separador para cadenas
string sepDigitos [] = {" ", ")", "=", "/", "*", "+", "-", "<", ">", "!", ";"}; //separador para digitos
string sepOprComp [] = {" ", "("}; //separador para Operaciones de comparacion
string sepFuncMat [] = {" ", "("}; //separador para funciones matematicas
string sepParAbir [] = {" ", "(", "\""}; //separador para parentesis abierto
string sepPareCer [] = {" ", "<", ">", "!", "+", "-", "/", "*", ")", "{", ";"};//separador para parentesis cerrado
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
char comillas = '"';

ifstream archivo;
char caracter;	// Variable que almacenara el caracter leido

int cont=0;	// Contador de tokens

int main(){
	string contenido;
	string token;
	string concatenar = "";
	int estado;
	int contToken = 0;
	archivo.open("prueba.txt");
	if(archivo == NULL){
		printf("El archivo no existe");
		exit(0);
	}else{
			
		
		while(!archivo.eof()){
			//printf("estado = %d\n", estado);
			archivo.get(caracter);
			//printf("****caracter = %c****\n\n", caracter);
			
			switch(estado){
				case 0:
					if(isalpha(caracter)){
						estado = 1;
						concatenar += caracter;
					}else if(isdigit(caracter)){
						estado = 2;
						concatenar += caracter;
					}else if(caracter == ','){
						estado = 3;
						concatenar += caracter;
					}else if(esOperadorComp(&caracter) == 1){
						printf("Op. Comparacion --> %c\n", caracter);
						estado = 5;
					}else if(esOperadorArit(&caracter) == 1){
						printf("Op. Aritmitico --> %c\n", caracter);
						estado = 6;
					}else if(caracter == opAsignacin){
						printf("Op. Asignacion --> %c\n", caracter);
						estado = 7;
					}else if(caracter == parenAbiert){
						printf("Paren. Abierto --> %c\n", caracter);
						estado = 8;
					}else if(caracter == parenCerrad){
						printf("Paren. Cerrado --> %c\n", caracter);
						estado = 9;
					}else if(esDelimitadors(&caracter) == 1){
						printf("Es Delimitador --> %c\n", caracter);
						estado = 10;
					}else if(esSaltosDLinea(&caracter) == 1){
						estado = 0;
						//printf("salto de linea, tab\n");
					}else if(caracter = comillas){
						estado = 0;
						concatenar += caracter;
						//printf("comillas\n");
					}else{
						printf("Error Case 0\n");
					}
				break;
				
				case 1:
					if(isalpha(caracter)){
						estado = 1;
						concatenar += caracter;
						if(concatenar == "Fin"){
							printf("Palabra Reservada --> %s\n", concatenar.c_str());
						}
					}else if(isdigit(caracter)){
						estado = 1;
						concatenar += caracter;
					}else if(esSepCadena(&caracter) == 1){
						estado = 0;
						if(caracter == '\"'){
							concatenar += caracter;
							printf("Msj. Impreso --> %s\n", concatenar.c_str());
						}else if(esPalabraReser(concatenar) == 1){
							printf("Palabra Reservada --> %s\n", concatenar.c_str());
						}else{
							printf("Identificador --> %s\n", concatenar.c_str());
						}
						archivo.unget();
						//concatenar += caracter;
						//printf("Separador --> %s\n", concatenar.c_str());
						concatenar = "";
					}
					else{
						printf("Error en el caso 1\n");
					}
				break;
				
				case 2:
					if(isdigit(caracter)){
						estado = 4;
						concatenar += caracter;
					}else if(caracter == ','){
						estado = 3;
						concatenar += caracter;
					}else if(esSepDigito(&caracter) == 1){
						estado = 0;
						archivo.unget();
						printf("Es un numero --> %s\n", concatenar.c_str());
						concatenar = "";
					}else if(caracter == EOF){
						printf("Es un numero --> %s\n", concatenar.c_str());
					}else{
						printf("Error en el Case 2\n");
					}
				break;
				
				case 3:
					if(isdigit(caracter)){
						estado = 4;
						concatenar += caracter;
					}else{
						printf("Error en el caso 3\n");
					}
				break;
				
				case 4:
					if(isdigit(caracter)){
						estado = 4;
						concatenar += caracter;
					}else if(esSepDigito(&caracter) == 1){
						archivo.unget();
						estado = 0;
						printf("Es un numero --> %s\n", concatenar.c_str());
						concatenar = "";
					}else{
						printf("Error en el caso 4\n");
					}
				break;
				
				case 5:
					if(esSepOprComparacion(&caracter) == 1){
						estado = 0;
						printf("Separador Op.Com --> %s\n", concatenar.c_str());
						concatenar = "";
					}else if(isalpha(caracter) || isdigit(caracter)){
						archivo.unget();
						estado = 0;
						concatenar = "";
					}else{
						printf("Error en el caso 5\n");
					}
				break;
				
				case 6:
					if(esSepFuncionesMat(&caracter) == 1){
						estado = 0;
						printf("Separador Op.Arit --> %s\n", concatenar.c_str());
						concatenar = "";
					}else if(isalpha(caracter) || isdigit(caracter)){
						archivo.unget();
						estado = 0;
						concatenar = "";
					}else{
						printf("Error en el caso 6\n");
					}
				break;
				
				case 7:
					if(caracter == ' '){
						estado = 0;
						printf("Sep. Op.Asignacion --> %s\n", concatenar.c_str());
						concatenar = "";
					}else if(isalpha(caracter) || isdigit(caracter)){
						archivo.unget();
						estado = 0;
						concatenar = "";
					}else{
						printf("Error en el caso 7\n");
					}
				break;
				
				case 8:
					if(esSepParentesAbier(&caracter) == 1){
						archivo.unget();
						estado = 0;
						printf("Sep. Parentesis --> %s\n", concatenar.c_str());
						concatenar = "";
					}else if(isalpha(caracter) || isdigit(caracter)){
						archivo.unget();
						estado = 0;
						concatenar = "";
					}else{
						printf("Error en el caso 8\n");
					}
				break;
				
				case 9:
					if(esSepParentesCerr(&caracter) == 1){
						archivo.unget();
						estado = 0;
						printf("Sep. Parentesis --> %s\n", concatenar.c_str());
						concatenar = "";
					}else{
						printf("Error en el caso 9\n");
					} 
				break;
				
				case 10:
					if(esSepDelimitadors(&caracter) == 1){
						archivo.unget();
						estado = 0;
						//printf("Es Separador --> Tab/espacio\n");
						concatenar = "";
					}else if(esSepDelimitadors(&caracter) == 1){
						archivo.unget();
						estado = 0;
						printf("Sep. Delimitadores --> %s\n", caracter);
						concatenar = "";
					}else{
						printf("Error en el caso 10\n");
					}
				break;
				
			}
			//if(estado != 0 || caracter != ' ' || caracter != '\t' || caracter != '\n'){
				
				
			//}
		}
	}
}

int esOperadorComp(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(operadorComparacio) / sizeof(operadorComparacio[0]);
	
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
	asize = sizeof(operadorAritmetico) / sizeof(operadorAritmetico[0]);
	
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
	asize = sizeof(palabrasReservadas) / sizeof(palabrasReservadas[0]);
	
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
	asize = sizeof(saltosdLin) / sizeof(saltosdLin[0]);
	
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
	asize = sizeof(delimitadores) / sizeof(delimitadores[0]);
	
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
	asize = sizeof(sepDigitos) / sizeof(sepDigitos[0]);
	
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
	asize = sizeof(sepOprComp) / sizeof(sepOprComp[0]);
	
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
	asize = sizeof(sepFuncMat) / sizeof(sepFuncMat[0]);

	for(i = 0; i < asize ; i++){
		if((sepFuncMat[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepParentesAbier(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepParAbir) / sizeof(sepParAbir[0]);
	
	for( i = 0 ; i < asize ; i++){
		if((sepParAbir[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}

int esSepParentesCerr(string letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(sepPareCer) / sizeof(sepPareCer[0]);
	
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
	asize = sizeof(sepDelimta) / sizeof(sepDelimta[0]);
	
	for( i = 0 ; i < asize ; i++ ){
		if((sepDelimta[i].compare(letra)) == 0){
			return 1;
		}
	}
	return 0;
}


