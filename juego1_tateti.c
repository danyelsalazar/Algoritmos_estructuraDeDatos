#include <stdio.h>
#include <time.h> //con esta bibliteca podemos usar  la funcion srand(time(NULL)); para crear numeros aleatorios

//juego de TATETI

void loop(char c [3][3]);//declaramos nuetra funcion loop osea el prototipo:

void Intro_Primera(char c [3][3]);//declaramos la funcion que llena nuestra matriz con los numero de casilla:

void tablero(char c[3][3]);//declaramos la funcion que muestra nuestra matriz:

void Seleccion_casilla(char c[3][3], int parar);//declaramos la funcion que usaremos para introducir nuestra eleccion:

void Seleccion_casilla_Oponente(char c[3][3], int parar);

int ganador(char c[3][3]);

int main(){
	char c [3][3];	//creamos una matriz de 3x3 de tipo char, recuerda filas x columnas
	
	loop(c);// llama a laas funciones fundamentales y hace un refresco de pantalla
	return 0;
}

//llama a laas funciones fundamentales y limpia la pantalla cuando sea necesario, recibe como argumento la matriz c de order 3x3
void loop(char c [3][3]){
	
	int i, parar; // para lo usaremos para finalizar el juego cuando ya se llenen todas las casillas
	//las inicializamos
	i = 0;
	parar = 1;
	
	Intro_Primera(c);//llenamos la matriz con los numeros de casillas
	
	do{
		system("cls");//limpiamos la pantalla en cada turno
		tablero(c);//mostramos el tablero de juego
		
		//verificamos de quien es el turno, nuestro turno sera cuando el resto de la division entre 1 y 2 sea 0, de lo
		//contrario sera el turno del oponente(en este caso es la pc)
		if(i % 2 == 0){
			Seleccion_casilla(c,parar);	//llamamos a la funcion que corresponde a nuestro turno
		}else{
			Seleccion_casilla_Oponente(c, parar);//llamamos a la funcion que corresponde al turno del oponente
			printf("Es el turno del oponente.....");
			sleep(1);//esperamos 1 segundo mientras el oponente pone su ficha 
			system("cls");//limpiamos pantalla asi no queda el print de la linea anterior
			tablero(c);//mostramos el tablero;
		}
		//verificamos si ya se lleno el tablero con el numero de turno y si ganador es 0 significa que hubo empate
		if(i == 9 && ganador(c) == 0){
				printf("Hubo un empate");
		}else{//de caso contrario vamos verificando quien gana primero
			if( ganador(c) == 1){//si ganador retorna 1 significa que gano X
				system("cls");//limpiamos pantalla
				tablero(c);//mostramos tablero
				printf("El ganador es X\n");
			    i = 10;// igualamos i a 10 asi finaliza el juego
			}else{
				if(ganador(c) == 2){//si ganador retorna 1 significa que gano O
					system("cls");//limpiamos pantalla
					tablero(c);//mostramos tablero
				    printf("El ganador es O \n");
					i = 10;//igualamos 1 a 10 asi finaliza el juego;
					}
				}
	    	}
		
		parar++;// incrementamos parar , de manera que cuando llegue a 9 el juego finalice
		i++;//incrementamos i 
		
	}while(i <= 9); // se ejecutara siempre que i sea menor o igual 9
	
}

//con esta funcion le daremos valores a la matriz
void Intro_Primera(char c [3][3]){
	
	int i, j;
	
	char auxiliar;
	
	auxiliar = '1'; // este lo usaremos para el valor de cada elemento de la matriz y lo iremos incrementando en cada vuelta, i fila j columna
	// el siguiente for basicamente primero itera la primera fila luego la segunda y luego la tercera, imagina una matriz como en algebra de 3x3:
	/*     a00 a01 a02
	       a10 a11 a12
		   a20 a21 a22
	*/
	for(i = 0; i < 3; i++){//con este recorremos fila
		for(j = 0; j < 3; j++){//con este recorremos la columna
			c[i][j] = auxiliar;
			auxiliar++;//incrementamos el valor del auxiliar
		}
	}
	
}

// con esta funcion mostramos nuestra matriz por panlla ordenada en forma de tabla
void tablero(char c [3][3]){
	int i, j;
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(j == 2){
				printf("  %c \n", c[i][j]);// si es el ultimo elemento de la columna hacemos un salto de linea
			}else{
				printf("  %c |", c[i][j]);//mostramos el elemnto junto con el signo | que usaremos para ir armando loa grilla
			}
		}
		if(i == 2){
			printf("\n");//hacemos un salto de linea al finalizar la ultima fila
		}else{
			printf("    |    |\n____|____|_____\n    |    |\n");//aqui vamos armando las grillas de la matriz , es cuestiion de ir probando hasta que quede centrado
		}
		
	}
}
//con esta funcion seleccionames la casilla donde pondremos nuestra ficha
void Seleccion_casilla(char c [3][3], int parar){
	char ficha;
	int i, j, k;
	do{
		do{
			printf("Elije la casilla para poner la ficha:");
			fflush(stdin);//Siempre limpian el buffer antes de pedir un caracter
			scanf("%c", &ficha);//lleemos el numero de casilla
		}while(ficha < '1' || ficha > '9');
		
		k = 0;
		
		//verificamos la posicion que se elijio y vemos si esta o no ocupada:(hacemos la verificacion para cada casilla o sea 9 veces, seguro esto lo podemos optimizar
		switch(ficha){
			case '1':
				i = 0;//asi vemos a que casillas corresponde el '1' , recuerda i es la fila j la columna entonce aqui i=0 y j= 0 representa el elemento a00 de la matriz y hacemos lo mismo en cada case
				j = 0;
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;//si la casilla esta ocupada k sera igual a 1 asi luego el bucle se repite
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '2':
				i = 0;
				j = 1;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '3':
				i = 0;
				j = 2;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '4':
				i = 1;
				j = 0;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '5':
				i = 1;
				j = 1;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '6':
				i = 1;
				j = 2;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '7':
				i = 2;
				j = 0;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '8':
				i = 2;
				j = 1;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
			case '9':
				i = 2;
				j = 2;
				
				if(c[i][j] == 'X' || c[i][j] == 'O'){
					k = 1;
					printf("La casilla esta ocupada, intentalo con otro numero\n\n");
				}
				break;
		}
	}while(k == 1); // se ejecuta mientras k sea 1 o sea mientras este ocupada la casilla selecionada
	
	c[i][j] = 'X';// cuando elijamos una casilla desocupada le asignamos X a dicha casilla
}


//aqui sera el oponente que dara un numero aleatorio
void Seleccion_casilla_Oponente(char c[3][3], int parar){
	int i, j, k;
		
	//inicializamos la semilla del generador de numeros aleatorios:
	srand(time(NULL));
	
	do{
		//estos i y j tendran un numero aleatorio para la posicion del O que pondra la pc 
		i = rand() % 3;//aleatorio entre 0 y 2
		j = rand() % 3;//aleatorio entre 0 y 2
		k = 0;// es igual que en la funcion anterior lo usamos para saber que la casilla selecionada esta ocupada en este caso la posicion seleccionada aleatoriamente
		
		if(c[i][j] == 'X' || c[i][j] == 'O'){
			k = 1;// si esta ocupada la posicion lo igualamos a 1 asi se repite el bucle hasta encontrar una posicion sin X ni O
		}
	}while(k == 1 && parar <= 9);// se ejecutara mientras que k sea 1 y parar menor o igual a 9 este parar representa la cantidad de turnos que existen en el juego asi que cuando ya se acaben los 9 turnos significa que ya el tablero se lleno por lo tanto tendra que haber acabado el juego
	
	c[i][j] = 'O';// si no esta ocupada la posiscion por X ni O entonces asignamos a dicha posicion una O
  
}
int ganador(char c[3][3]){
	
	// retorna 1 cuango gana X 
	//combinaciones en lineas rectas horizontales---------
	if((c[0][0] == 'X') && (c[0][1] == 'X') && (c[0][2] == 'X')){
		return 1;
	}
	if((c[1][0] == 'X') && (c[1][1] == 'X') && (c[1][2] == 'X')){
		return 1;
	}
	if((c[2][0] == 'X') && (c[2][1] == 'X') && (c[2][2] == 'X')){
		return 1;
	}
	//combinaciones en lineas rectas verticales
	if((c[0][0] == 'X') && (c[1][0] == 'X') && (c[2][0] == 'X')){
		return 1;
	}
	if((c[0][1] == 'X') && (c[1][1] == 'X') && (c[2][1] == 'X')){
		return 1;
	}
	if((c[0][2] == 'X') && (c[1][2] == 'X') && (c[2][2] == 'X')){
		return 1;
	}
	//combinaciones de laterales
	if((c[0][0] == 'X') && (c[1][1] == 'X') && (c[2][2] == 'X')){
		return 1;
	}
	if((c[0][2] == 'X') && (c[1][1] == 'X') && (c[2][0] == 'X')){
		return 1;
	}
	
	//retorna 2 si gana O
	
	//combinaciones en lineas rectas horizontales---------
	if((c[0][0] == 'O') && (c[0][1] == 'O') && (c[0][2] == 'O')){
		return 2;
	}
	if((c[1][0] == 'O') && (c[1][1] == 'O') && (c[1][2] == 'O')){
		return 2;
	}
	if((c[2][0] == 'O') && (c[2][1] == 'O') && (c[2][2] == 'O')){
		return 2;
	}
	//combinaciones en lineas rectas verticales
	if((c[0][0] == 'O') && (c[1][0] == 'O') && (c[2][0] == 'O')){
		return 2;
	}
	if((c[0][1] == 'O') && (c[1][1] == 'O') && (c[2][1] == 'O')){
		return 2;
	}
	if((c[0][2] == 'O') && (c[1][2] == 'O') && (c[2][2] == 'O')){
		return 2;
	}
	//combinaciones de laterales
	if((c[0][0] == 'O') && (c[1][1] == 'O') && (c[2][2] == 'O')){
		return 2;
	}
	if((c[0][2] == 'O') && (c[1][1] == 'O') && (c[2][0] == 'O')){
		return 2;
	}
	 // SI HAY EMPATE RETORNA 0:
	return 0;
}







