#include "prime.h"
#include <limits.h>

//Contatore globale
static unsigned short int primo_succ = 0;

//Funzione per vedere se è un numero primo. Se è primo ritorna 1, se non lo è ritorna 0.
unsigned short int is_prime(unsigned short int n) {
	if (n == 0 || n == 1) return 0;
	int i;
	for (i = 2; i < (n / 2) + 1; i++)
	{
		//appena trova anche soltanto un divisore del numero inserito in input, ritorna 0
		if (n % i == 0)
			return 0;
	}
	//se non trova nessun divisore esce dal for normalmente e ritorna 1
	return 1;
}

//Funzione che, in base ad un numero inserito in input, restituisce il numero primo in quella posizione.
//Esempio: posizione 0 --> 2, posizione 1 --> 3, posizione 2 --> 5, etc..-
unsigned short int nth_prime(unsigned short int n) {
	int i = 2, c = 0;
	while (c <= n)
	{
		i++;
		//Richiamo la funzione precedente. Se il numero è primo lo aggiungo nella variabile contatore.
		if (is_prime(i) == 1)
		{
			c++;
		}

		//Controllo in caso di overflow se il numero è troppo grande
		if (i == USHRT_MAX)
			return 0;
	}
	//Restituisce il numero primo 
	return i;
}

//DA FINIRE
unsigned short int succ_prime(int reset) {


    unsigned short int num = primo_succ == 0 ? 2 : primo_succ + 1;
	if (reset != 0)
	{
		primo_succ = 2;
		return 2;
	}

	while (is_prime(num) == 0) {
		num++;
		if (num >= USHRT_MAX)
		{
			primo_succ = 0;
			return 0;
		}
	}
	primo_succ = num;

	return num;
}

//Funzione che, dati due numeri non necessariamente primi, restituisce 0 se hanno almeno 1 divisore comune, se no restituisce 1 e sono coprimi.
unsigned short int co_prime(unsigned short int m, unsigned short int n) {
	int i, min = m;
	//controllo qual è il numero più piccolo tra i due, così da esser sicura di calcolare tutti i possibili divisori in comune.
	if (m > n)
		min = n;

	for (i = 2; i <= min; i++)
	{
		//appena un numero è divisore di entrambi i numeri, allora non sono coprimi e restituisce 0
		if (n % i == 0 && m % i == 0)
			return 0;
	}
	//se non trova nessun divisore esce dal for normalmente e ritorna 1, quindi sono coprimi
	return 1;
}




