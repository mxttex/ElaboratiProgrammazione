#include<stdio.h>
#include<limits.h>
#include<float.h>

void main() {
    /*dichiarazione e assegnazione variabili, una ciascuna per ogni tipo e modificatore*/
    char c = 'c';
    int i = 10;
    float f = 3.14;
    double d = 5.5;
    signed char sc = "-10";
    unsigned char uc = "3";
    signed int si = -67;
    unsigned int ui = 17;
    short int shi = 1;
    signed short int ssi = -255;
    unsigned short int usi = 254;
    long int li = 1000;
    signed long int sli = -1234;
    unsigned long int uli = 468793575748;
    long double ld = 7.568;

    /*stampa a console per ogni variabile, seguendo il formato: 
    TYPE: char NAME: c VALUE: x MIN: -128 MAX: 127 BYTE: 1
    */

    printf("TYPE: char NAME: \"c\" VALUE: %c MIN: %d MAX: %d BYTE: %d\n", c, CHAR_MIN, CHAR_MAX, sizeof(c));
    printf("TYPE: signed char NAME: \"sc\" VALUE: %c MIN: %d MAX: %d BYTE: %d\n", sc, SCHAR_MIN, SCHAR_MAX, sizeof(sc));
    printf("TYPE: unsigned char NAME: \"uc\" VALUE: %c MIN: %d MAX: %d BYTE: %d\n", uc, 0, UCHAR_MAX, sizeof(uc));
    printf("TYPE: int NAME: \"i\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", i, INT_MIN, INT_MAX, sizeof(i));
    printf("TYPE: float NAME: \"f\" VALUE: %f MIN: %e MAX: %e BYTE: %d\n", f, FLT_MIN, FLT_MAX, sizeof(f));
    printf("TYPE: double NAME: \"d\" VALUE: %f MIN: %e MAX: %e BYTE: %d\n", d, DBL_MIN, DBL_MAX, sizeof(d));
    printf("TYPE: int NAME: \"si\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", si, INT_MIN, INT_MAX, sizeof(si));
    printf("TYPE: unsigned int NAME: \"ui\" VALUE: %u MIN: %d MAX: %d BYTE: %d\n", ui, INT_MIN, UINT_MAX, sizeof(ui));
    printf("TYPE: short int NAME: \"shi\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", shi, SHRT_MIN, SHRT_MAX, sizeof(shi));
    printf("TYPE: short signed int NAME: \"ssi\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", ssi, SHRT_MIN, SHRT_MAX, sizeof(ssi));
    printf("TYPE: short unsigned int NAME: \"usi\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", usi, SHRT_MIN, USHRT_MAX, sizeof(usi));
    printf("TYPE: long int NAME: \"li\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", li, LONG_MIN, LONG_MAX, sizeof(li));
    printf("TYPE: signed long int NAME: \"sli\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", sli, LONG_MIN, LONG_MAX, sizeof(sli));
    printf("TYPE: unsigned long int NAME: \"uli\" VALUE: %d MIN: %d MAX: %d BYTE: %d\n", uli, 0UL, ULONG_MAX, sizeof(uli));
    printf("TYPE: long double NAME: \"ld\" VALUE: %e MIN: %e MAX: %e BYTE: %d", ld, LDBL_MIN, LDBL_MAX, sizeof(ld));

    return 0;
}
