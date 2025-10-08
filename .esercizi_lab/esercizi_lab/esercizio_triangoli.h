void esercizio_triangoli() {
	//la difficilissima selezione if
	int alfa, beta, gamma; // ampiezza angoli , in gradi
	printf(" Che tipo di triangolo abbiamo ? \n Inserisci l ’ ampiezza dei tre angoli in gradi : ");
	scanf("%d %d %d", &alfa, &beta, &gamma);
	/* Dobbiamo c o n t r o l l a r e :
	- se un triangolo
	- se r ett ango lo
	- se equilatero , isoscele o scaleno
	*/
	int sommaGradi = alfa + beta + gamma;
	if (!(sommaGradi == 180))
		printf("non e' un triangolo");
	else {
		if (alfa == 90 || beta == 90 || gamma == 90) {
			printf("Il triangolo è rettangolo\n");
		}
		if (alfa == 60)
			printf("Il triangolo è equilatero\n");
		else if (alfa == beta || beta == gamma || gamma == alfa)
			printf("Il triangolo è isoscele\n");
		else
			printf("Il triangolo è scaleno");
	}

	// printf (" I tre angoli non fanno parte di un t rian gol o \ n ") ;
}
