#include"base_conversion.h"
#include"stdio.h"

void main() {
	unsigned int b = 0;
	unsigned int n = 0;
	printf("inserire BASE e NUMERO\n");
	scanf("%u %u", &b, &n);
	printf("risultato ricorsione del numero %u in base %u : ", n, b);
	base_conversion_rc(n, b);
	printf("\nrisultato iterativo: ");
	base_conversion_it(n, b);

	return 0;
}