#include "base_conversion.h"
#include "math.h"

static unsigned int howManyDigits(unsigned int n, unsigned int b) {
	/*calcolo il numero di cifre. visto che in c non ci sono funzioni in cui posso passare la base:
	calcolo il nunmero di cifre calcolando il logaritmo in base e sfruttando la formula di cambio base.
	grazie alla funzione ceil prendo il numero intero + piccolo vicino al risultato della divisione
	*/
	return (unsigned int)ceil(log(n + 1) / log(b));
}

void base_conversion_rc(unsigned int n, unsigned int b) {
	//se il numero non ha la bse compresa tra 2 e 16 non faccio nulla
	if (b > 2 || b < 16)
	{
		unsigned int resto = 0;
		//calcolo il risultato della divisione, necessaria per continuare le divisioni successive
		unsigned int divisione = n / b;
		//prendo il resto, necessario per la costruzione del numero
		resto = n % b;
		
		//se la base e' maggiore del numero ricevuto dalla funzione vuol dire che abbiamo finito le divisioni successive
		if (b > n) {
			//stampo il resto, i risultati sono gia al contrario perche' le chiamate alle funzioni nello stack sono gestite in modo LIFO
			resto < 10 ? printf("%u", resto) : printf("%c", resto + 55); //aggiungo il numero 55 se il resto e' maggiore di 10,
			//in modo da poter usare le lettere A = 10, B = 11, C = 12, D = 13, E= 14, F=15 (ASCII TABLE)
		}
		else {
			//chiamata ricorsiva per continuare le divisioni successive
			base_conversion_rc(divisione, b);
			resto < 10 ? printf("%u", resto) : printf("%c", resto + 55);
		}
	}
}

void base_conversion_it(unsigned int n, unsigned int b) {
	/*per prima cosa, mi serve capire quante cifre servono per rappresentare il numero grazie alla formula
	  k = ⌈logb(n + 1)⌉ --> lo calcolo con la funzione howManyDigits
	*/
	if (n == 0) printf("%d", 0);

	unsigned int k = howManyDigits(n, b);
	unsigned int divisione = n;
	int i = k-1;

	//se il numero uguale a zero, a causa dell'arrotondamneto di ceil non entra nel ciclo
	for (i; i >= 0; i--) {
		divisione = n / pow(b, i);
		unsigned int resto = divisione % b;
		
		resto < 10 ? printf("%u", resto) : printf("%c", resto + 55);
	}
}

