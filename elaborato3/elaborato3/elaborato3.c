#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    unsigned int x;
    unsigned int res1 = 0, res2 = 0, res3 = 0;
    printf("Inserisci un intero positivo: "); scanf("%u", &x);

    int tmp = x, resto = 0;
    //variabili contatori
    int nCifre = 0, nzeri = 0;
    //Numero al contrario: prendo resto di un numero, moltiplico per 10 e aggiungo resto successivo
    while (tmp > 0)
    {
        nCifre++;
        resto = tmp % 10;
        //visto che già controllo cifra per cifra singolarmente, tengo già conto degli zeri
        if (resto == 0)
            nzeri++;

        //divido per 10 così da rimuovere la parte del numero di cui ho già preso il resto.
        tmp = tmp / 10;
        res1 = res1 * 10 + resto;
    }

    //Complemento a 10. La potenza da assegnare al 10 equivale al numero di cifre del numero inserito in input  
    res2 = (x == 0 ? 10 : pow(10, nCifre) - x);

    // Gli zeri li avevo contati precedentemente nel primo ciclo.
    res3 = (x == 0 ? 1 : nzeri);

    //do NOT add code after this point
    //OUTPUT
    printf("\nRisultati\n");
    printf("Numero al contrario: %u\nComplemento a 10: %u\nNumero di zeri: %u\n", res1, res2, res3);

    //DON'T REMOVE from submittion
#ifdef EVAL
    eval(x, res1, res2, res3);
#endif
    return 0;
}
