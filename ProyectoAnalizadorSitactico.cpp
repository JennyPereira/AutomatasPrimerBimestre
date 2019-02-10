#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/******************************************************************************************************************/
/*												LEXICO															*/
/******************************************************************************************************************/

/*											  SEPARADORES														*/

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
/******************************************************************************************************************/
/*												FIN LEXICO														*/
/******************************************************************************************************************/

string tAccion[126][3] = {{"Inicio", "0", "s2"}, {"$", "1", "acc"}, {":", "2", "s3"}, {"id", "3", "s8"}, {"entero", "3", "s12"}, 
						{"si", "3", "s10"}, {"Fin", "4", "s13"}, {"Fin", "5", "r3"}, {"id", "5", "s8"}, {"entero", "5", "s12"}, 
						{"si", "5", "s10"}, {"}", "5", "r3"}, {"Fin", "6", "r4"}, {"id", "6", "r4"}, {"entero", "6", "r4"}, 
						{"si", "6", "r4"}, {"}", "6", "r4"}, {"Fin", "7", "r5"}, {"id", "7", "r5"}, {"entero", "7", "r5"}, 
						{"si", "7", "r5"}, {"}", "7", "r5"}, {"=", "8", "s15"}, {"Fin", "9", "r7"}, {"id", "9", "r7"}, 
						{"entero", "9", "r7"}, {"si", "9", "r7"}, {"}", "9", "r7"}, {"(", "10", "s16"}, {"id", "11", "s17"}, 
						{"id", "12", "r9"}, {"$", "13", "r1"}, {"Fin", "14", "r2"}, {"}", "14", "r2"}, {"id", "15", "s22"}, 
						{"(", "15", "s21"}, {"id", "16", "s22"}, {"(", "16", "s21"}, {";", "17", "s24"}, {";", "18", "s25"}, 
						{"+", "18", "s26"}, {";", "19", "r13"}, {"<", "19", "r13"}, {")", "19", "r13"}, {">", "19", "r13"}, 
						{"+", "19", "r13"}, {"-", "19", "s27"}, {";", "20", "r15"}, {"<", "20", "r15"}, {")", "20", "r15"}, 
						{">", "20", "r15"}, {"+", "20", "r15"}, {"-", "20", "r15"}, {"id", "21", "s22"}, {"(", "21", "s21"}, 
						{";", "22", "r17"}, {"<", "22", "r17"}, {")", "22", "r17"}, {">", "22", "r17"}, {"+", "22", "r17"}, 
						{"-", "22", "r17"}, {"<", "23", "s29"}, {">", "23", "s29"}, {"+", "23", "s29"}, {"Fin", "24", "r8"}, 
						{"id", "24", "r8"}, {"entero", "24", "r8"}, {"si", "24", "r8"}, {"}", "24", "r8"}, {"Fin", "25", "r6"}, 
						{"id", "25", "r6"}, {"entero", "25", "r6"}, {"si", "25", "r6"}, {"}", "25", "r6"}, {"id", "26", "s22"}, 
						{"(", "26", "s21"}, {"id", "27", "s22"}, {"(", "27", "s21"}, {")", "28", "s33"}, {"+", "28", "s26"}, 
						{"id", "29", "s22"}, {"(", "29 ", "s21"}, {"id", "30", "s22"}, {"(", "30", "s21"}, {";", "31", "r12"}, 
						{"<", "31", "r12"}, {")", "31", "r12"}, {">", "31", "r12"}, {"+", "31", "r12"}, {"-", "31", "s27"}, 
						{";", "32", "r14"}, {"<", "32", "r14"}, {")", "32", "r14"}, {">", "32", "r14"}, {"+", "32", "r14"}, 
						{"-", "32", "r14"}, {";", "33", "r16"}, {"<", "33", "r16"}, {")", "33", "r16"}, {">", "33", "r16"}, 
						{"+", "33", "r16"}, {"-", "33", "r16"}, {")", "34", "s36"}, {"+", "34", "s26"}, {")", "35", "s37"}, 
						{"+", "35", "s26"}, {"{", "36", "s38"}, {"{", "37", "s39"}, {"id", "38", "s8"}, {"entero", "38", "s12"}, 
						{"si", "38", "s10"}, {"id", "39", "s8"}, {"entero", "39", "s12"}, {"si", "39", "s10"}, {"}", "40", "s42"}, 
						{"}", "41", "s43"}, {"Fin", "42", "r10"}, {"id", "42", "r10"}, {"entero", "42", "r10"}, {"si", "42", "r10"}, 
						{"}", "42", "r10"}, {"Fin", "43", "r11"}, {"id", "43", "r11"}, {"entero", "43", "r11"}, {"si", "43", "r11"}, 
						{"}", "43", "r11"}};

 
string ir_A[43][3] = {{"G", "0", "1"}, {"P", "3", "4"}, {"S", "3", "5"}, {"DV", "3", "6"}, {"V", "3", "9"}, {"Ti", "3", "11"}, 
					{"ECif", "3", "7"}, {"P", "5", "14"}, {"S", "5", "5"}, {"DV", "5", "6"}, {"V", "5", "9"}, {"Ti", "5", "11"}, 
					{"ECif", "5", "7"}, {"E", "15", "18"}, {"T", "15", "19"}, {"F", "15", "20"}, {"E", "16", "23"}, {"T", "16", "19"}, 
					{"F", "16", "20"}, {"E", "21", "28"}, {"T", "21", "19"}, {"F", "21", "20"}, {"T", "26", "31"}, {"F", "26", "20"}, 
					{"F", "27", "32"}, {"E", "29", "34"}, {"T", "29", "19"}, {"F", "29", "20"}, {"E", "30", "35"}, {"T", "30", "19"}, 
					{"F", "30", "20"}, {"P", "38", "40"}, {"S", "38", "5"}, {"DV", "38", "6"}, {"V", "38", "9"}, {"Ti", "38", "11"}, 
					{"ECif", "38", "7"}, {"P", "39", "41"}, {"S", "39", "5"}, {"DV", "39", "6"}, {"V", "39", "9"}, {"Ti", "39", "11"}, 
					{"ECif", "39", "7"}};

//son la longitud que contiene cada regla 
string longitudR [17][2] = {{"r1", "4"}, {"r2", "2"}, {"r3", "1"}, {"r4", "1"}, {"r5", "1"}, {"r6", "4"}, {"r7", "1"}, {"r8", "3"}, 
						{"r9", "1"}, {"r10", "9"}, {"r11", "9"}, {"r12", "3"}, {"r13", "1"}, {"r14", "3"}, {"r15", "1"}, {"r16", "3"}, 
						{"r17", "1"}};
						
//hace referencia a las reglas de la gramática de la parte izquierda
string reglaR [17][2] = {{"r1", "G"}, {"r2", "P"}, {"r3", "P"}, {"r4", "S"}, {"r5", "S"}, {"r6", "S"}, {"r7", "DV"}, 
						{"r8", "V"}, {"r9", "Ti"}, {"r10", "ECif"}, {"r11", "ECif"}, {"r12", "E"}, {"r13", "E"}, {"r14", "T"}, 
						{"r15", "T"}, {"r16", "F"}, {"r17", "F"}};

//analizador lexico
struct Nodo{
    string state;
    Nodo *anterior;
};
//agregarPila = addPile --- estado = state --- pila=pile
void addPile(Nodo *&pile, string state){
	Nodo *nuevo = new Nodo();
	nuevo->state = state;
	nuevo->anterior = pile;
	pile = nuevo;
}

void deletePile(Nodo *&pile){
	Nodo *aux = pile;
	pile = aux->anterior;
	delete aux;
}
//accion = ACCION
string ACCION(string state, string symbol){
	//printf("entra %s\n", symbol.c_str());
	
	for(int i = 0; i < 126; i++){
		//printf("i = %d\n", i);
		//printf("i = %s\n", tAccion[i][0].c_str());
		if(symbol == tAccion[i][0] && state == tAccion[i][1]){
			return tAccion[i][2];
		}
	}
	printf("probablemente algo esta mal en el programa, revise porfavor\n");
}

string irA(string regla, string state){
	for(int i = 0; i < 43; i++){
		if(regla == ir_A[i][0] && state == ir_A[i][1]){
			return ir_A[i][2];
		}
	}
}

int getLongitud(string regla){
	//printf("regla %s\n", regla.c_str());
	string aux = "";
	int longitud = 0;
	for(int i = 0; i < 17; i++){
		if(regla == longitudR[i][0]){
			aux = longitudR[i][1];
			longitud = atoi(aux.c_str());
			return longitud;
		}
	}
}

string getRegla(string regla){
	for(int i = 0; i < 17; i++){
		if(regla == reglaR[i][0]){
			return reglaR[i][1];
		}
	}
}

//SEPARADORES DEL ANALIZADOR LÉXICO

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

string lexico(){
	string contenido;
	string token;
	string concatenar = "";
	int estado;
	int contToken = 0;
	//archivo.open("prueba.txt");
	if(archivo == NULL){
		printf("El archivo no existe... chan chan chan");
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
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 5;
						return token;
					}else if(esOperadorArit(&caracter) == 1){
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 6;
						return token;
					}else if(caracter == opAsignacin){
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 7;
						return token;
					}else if(caracter == parenAbiert){
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 8;
						return token;
					}else if(caracter == parenCerrad){
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 9;
						return token;
					}else if(esDelimitadors(&caracter) == 1){
						token = caracter;
						printf("Token --> %s\n", token.c_str());
						estado = 10;
						return token;
						printf("aqui");
					}else if(esSaltosDLinea(&caracter) == 1){
						estado = 0;
						//printf("salto de linea, tab\n");
					}else if(caracter == comillas){
						estado = 0;
						concatenar += caracter;
						//printf("comillas\n");
					}else if(caracter == '$'){
						token = caracter;
						return "$";
					}else{
						printf("Error Case 0\n");
					}
				break;
				
				case 1:
					if(isalpha(caracter)){
						estado = 1;
						concatenar += caracter;
						token = concatenar.c_str();
						if(concatenar == "Fin"){
							printf("Token fin--> %s\n", token.c_str());
							estado = 0;
							//archivo.unget();
							//archivo.get(caracter);
							return token;
						}
					}else if(isdigit(caracter)){
						estado = 1;
						concatenar += caracter;
					}else if(esSepCadena(&caracter) == 1){
						estado = 0;
						if(caracter == '\"'){
							concatenar += caracter;
							token = concatenar;
							printf("Msj. Impreso --> %s\n", concatenar.c_str());
						}else if(esPalabraReser(concatenar) == 1){
							archivo.unget();
							printf("TokenPR --> %s\n", token.c_str());
							return token;
						}else{
							archivo.unget();
							token = "id";
							printf("Token --> %s\n", token.c_str());
							return token;
						}
						archivo.unget();
						//concatenar += caracter;
						//printf("Separador --> %s\n", concatenar.c_str());
						concatenar = "";
						//return token;
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
						token = caracter;
						return "id";
					}else if(caracter == EOF){
						printf("Es un numero --> %s\n", concatenar.c_str());
						token = caracter;
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
						//archivo.unget();
						estado = 0;
						token = "id";
						printf("Token --> %s\n", token.c_str());
						concatenar = "";
						return token;
					}else{
						printf("Error en el caso 4\n");
					}
				break;
				
				case 5:
					if(esSepOprComparacion(&caracter) == 1){
						estado = 0;
						concatenar = "";
						if (caracter == ' ' || caracter == '\n' || caracter == '\t'){
							
						}else{
							token=caracter;
							//printf("Separador Op.Com --> %s\n", concatenar.c_str());
						}
					}else if(isalpha(caracter) || isdigit(caracter)){
						//archivo.unget();
						estado = 0;
						concatenar = "";
					}else{
						printf("Error en el caso 5\n");
					}
				break;
				
				case 6:
					if(esSepFuncionesMat(&caracter) == 1){
						estado = 0;
						//printf("Separador Op.Arit --> %s\n", concatenar.c_str());
						concatenar = "";
						if (caracter == ' ' || caracter == '\n' || caracter == '\t'){
							
						}else{
							token=caracter;
							//printf("Separador Op.Arit --> %s\n", concatenar.c_str());
						}
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
						concatenar = "";
						if (caracter == ' ' || caracter == '\n' || caracter == '\t'){
							
						}else{
							//printf("Sep. Op.Asignacion --> %s\n", concatenar.c_str());
						}
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
						concatenar = "";
						/*if (concatenar.c_str() == " " || concatenar.c_str() == "\n" || concatenar.c_str() == "\t"){
							
						}else{
							printf("Sep. Parentesis caso 8 --> %s\n", concatenar.c_str());
						}*/
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
						if (concatenar.c_str() != " " || concatenar.c_str() != "\n" || concatenar.c_str() != "\t"){ 
							
						}else{
							
						}
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
						//printf("Sep. Delimitadores --> %s\n", caracter);
						concatenar = "";
						if (caracter == ' ' || caracter == '\n' || caracter == '\t'){
							
						}else{
							//printf("Sep. Delimitadores --> %s\n", concatenar.c_str());
						}
					}else{
						printf("Error en el caso 10\n");
					}
				break;	
			}
		}
	}
	archivo.close();
}

int main(){
	archivo.open("prueba.txt");
	string a = "";
	
	Nodo *pile = NULL;
	string s = "0";
	addPile(pile,s);
	
	string t ="";
	
	int aux = 0;
	string regla = "";
	
	a = lexico();
	
	while(a != "eof"){
		//printf("entra %s\n", a.c_str());
		//hacer que ''
		s = pile->state;
		
		t = ACCION(s,a);
		
		printf("s = %s\n", s.c_str());
		printf("a = %s\n", a.c_str());
		
		if(t.substr(0,1) == "s"){
			//meter en pila
			addPile(pile, t.substr(1,t.length()));
			//hacer que 'a' sea el siguiente simbolo
			a = lexico();
			
			printf("t = %s\n", t.c_str());
			printf("-------------------------------------------------\n");
		}else if(t.substr(0,1) == "r"){
			printf("t = %s\n", t.substr(0,1).c_str());
			printf("-------------------------------------------------\n");
			//sacar n simbolos de la pila
			aux = getLongitud(t);
			for(int i = 0; i < aux; i++){
				deletePile(pile);
			}
			
			//obtener regla
			regla = getRegla(t);

			s = irA(regla,pile->state);
			//agregar
			addPile(pile,s);
			   
		}else if(t == "acc"){
			a = "eof";
			printf("\ntodo bien\n");
		}
		
	}
}

