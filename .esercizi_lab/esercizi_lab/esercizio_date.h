void esercizio_date() {
	unsigned int giorno, mese, anno = 0;

	printf("Inserire giorno, mese e anno: ");
	scanf("%u %u %u", &giorno, &mese, &anno);

	printf("%u ", giorno);

	switch (mese) {
	case 1:  printf("gennaio "); break;
	case 2:  printf("febbraio "); break;
	case 3:  printf("marzo "); break;
	case 4:  printf("aprile "); break;
	case 5:  printf("maggio "); break;
	case 6:  printf("giugno "); break;
	case 7:  printf("luglio "); break;
	case 8:  printf("agosto "); break;
	case 9:  printf("settembre "); break;
	case 10: printf("ottobre "); break;
	case 11: printf("novembre "); break;
	case 12: printf("dicembre "); break;
	default:
		printf("(mese non valido) ");
		break;
	}

	printf("%u\n", anno);
}