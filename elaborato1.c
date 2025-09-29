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

    printf("TYPE: char NAME: \"c\" VALUE: %c MIN: %d MAX: %d BYTE: %u\n", c, CHAR_MIN, CHAR_MAX, sizeof(c));
    printf("TYPE: signed char NAME: \"sc\" VALUE: %c MIN: %d MAX: %d BYTE: %u\n", sc, SCHAR_MIN, SCHAR_MAX, sizeof(sc));
    printf("TYPE: unsigned char NAME: \"uc\" VALUE: %c MIN: %d MAX: %d BYTE: %u\n", uc, 0, UCHAR_MAX, sizeof(uc));
    printf("TYPE: int NAME: \"i\" VALUE: %d MIN: %d MAX: %d BYTE: %u\n", i, INT_MIN, INT_MAX, sizeof(i));
    printf("TYPE: signed int NAME: \"si\" VALUE: %d MIN: %d MAX: %d BYTE: %u\n", si, INT_MIN, INT_MAX, sizeof(si));
    printf("TYPE: unsigned int NAME: \"ui\" VALUE: %u MIN: %d MAX: %d BYTE: %u\n", ui, 0, UINT_MAX, sizeof(ui));
    printf("TYPE: short int NAME: \"shi\" VALUE: %hd MIN: %d MAX: %d BYTE: %u\n", shi, SHRT_MIN, SHRT_MAX, sizeof(shi));
    printf("TYPE: short signed int NAME: \"ssi\" VALUE: %hd MIN: %d MAX: %d BYTE: %u\n", ssi, SHRT_MIN, SHRT_MAX, sizeof(ssi));
    printf("TYPE: unsigned short int NAME: \"usi\" VALUE: %hu MIN: %d MAX: %d BYTE: %u\n", usi, 0, USHRT_MAX, sizeof(usi));
    printf("TYPE: long int NAME: \"li\" VALUE: %ld MIN: %d MAX: %d BYTE: %u\n", li, LONG_MIN, LONG_MAX, sizeof(li));
    printf("TYPE: signed long int NAME: \"sli\" VALUE: %ld MIN: %d MAX: %d BYTE: %u\n", sli, LONG_MIN, LONG_MAX, sizeof(sli));
    printf("TYPE: unsigned long int NAME: \"uli\" VALUE: %lu MIN: %d MAX: %d BYTE: %u\n", uli, 0LU, ULONG_MAX, sizeof(uli));
    printf("TYPE: float NAME: \"f\" VALUE: %f MIN: %e MAX: %e BYTE: %u\n", f, FLT_MIN, FLT_MAX, sizeof(f));
    printf("TYPE: double NAME: \"d\" VALUE: %f MIN: %e MAX: %e BYTE: %u\n", d, DBL_MIN, DBL_MAX, sizeof(d));
    printf("TYPE: long double NAME: \"ld\" VALUE: %lf MIN: %e MAX: %e BYTE: %u\n", ld, LDBL_MIN, LDBL_MAX, sizeof(ld));

    return 0;
}