void da10aNRicorsiva(unsigned int b, unsigned int n) {
	if (b > 2 || b < 16)
	{
		int resto = 0;
		int divisione = n / b;
		resto = n % b;
		if (b > n) {
			resto < 10 ? printf("%d", resto) : printf("%c", resto + 55);
		}
		else {
			da10aNRicorsiva(b, divisione);
			resto < 10 ? printf("%d", resto) : printf("%c", resto + 55);
		}
	}
}
