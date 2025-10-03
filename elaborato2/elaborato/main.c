#include<stdio.h>
#include<math.h>
#include "quadratic_eq.h" //con "" invece di <>, perche' il file e' nella stessa cartella del file main.c

void main() {
	/*Implementare le seguenti macro per calcolare alcune proprietà di una
		funzione di secondo grado nel campo reale :
	f(x) = ax^2 + bx + c*/

	//dichiarazione variabili
	float a = 0;
	float b = 0;
	float c = 0;

	//valori della funzione presi in input
	printf("Tenendo in considerazione f(x) = ax^2 + bx + c\nInserire il valore di A\n");
	scanf("%f", &a);
	while (a == 0) {
		printf("A non puo' essere 0, reinserire il valore di A\n");
		scanf("%f", &a);
	}
	printf("Inserire il valore di B\n");
	scanf("%f", &b);
	printf("Inserire il valore di C\n");
	scanf("%f", &c);

	//switch che in base al numero di soluzione stampa quante soluzioni ha la funzione 
	switch (NUM_OF_ROOTS(a, b, c)) {
	case 0:
		printf("L'equazione non ha soluzioni");
		break;
	case 1:
		printf("L'equazione si risolve in x = %f", ROOT1(a, b, c));
		break;
	default:
		printf("L'equazione si risolve in x1 = %f e in x2 = %f\n", ROOT1(a, b, c), ROOT2(a, b, c));
		break;
	};

	printf("La funzione ha un punto di %s in %f\n",
		(MAXIMUM_POINT(a, b, c) ? "massimo" : "minimo"),
		EXTREME_POINT(a, b, c));
	/*printf("La funzione ha un punto di %d in %f\n",
		(MAXIMUM(a, b, c) ),
		EXTREME_POINT(a, b, c));*/
	return 0;
}