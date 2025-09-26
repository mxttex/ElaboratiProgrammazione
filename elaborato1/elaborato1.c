#include<stdio.h>
#include<limits.h>
#include<float.h>

void main() {

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

    printf("TYPE: char NAME: \"c\" VALUE: %c MIN: %d MAX: %d BYTE: %d ", c, CHAR_MIN, CHAR_MAX, sizeof(c));
    printf("\nTYPE: int NAME: \"i\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", i, INT_MIN, INT_MAX, sizeof(i));
    printf("\nTYPE: float NAME: \"f\" VALUE: %f MIN: %f MAX: %e BYTE: %d ", f, FLT_MIN, FLT_MAX, sizeof(f));
    printf("\nTYPE: double NAME: \"d\" VALUE: %f MIN: %f MAX: %e BYTE: %d ", d, DBL_MIN, DBL_MAX, sizeof(d));
    printf("\nTYPE: char NAME: \"sc\" VALUE: %c MIN: %d MAX: %d BYTE: %d ", sc, SCHAR_MIN, SCHAR_MAX, sizeof(sc));
    printf("\nTYPE: char NAME: \"uc\" VALUE: %c MIN: %d MAX: %d BYTE: %d ", uc, SCHAR_MIN, UCHAR_MAX, sizeof(uc));
    printf("\nTYPE: int NAME: \"si\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", si, INT_MIN, INT_MAX, sizeof(si));
    printf("\nTYPE: int NAME: \"ui\" VALUE: %u MIN: %d MAX: %d BYTE: %d ", ui, INT_MIN, UINT_MAX, sizeof(ui));
    printf("\nTYPE: int NAME: \"shi\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", shi, SHRT_MIN, SHRT_MAX, sizeof(shi));
    printf("\nTYPE: int NAME: \"ssi\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", ssi, SHRT_MIN, SHRT_MAX, sizeof(ssi));
    printf("\nTYPE: int NAME: \"usi\" VALUE: %u MIN: %d MAX: %d BYTE: %d ", usi, SHRT_MIN, USHRT_MAX, sizeof(usi));
    printf("\nTYPE: int NAME: \"li\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", li, LONG_MIN, LONG_MAX, sizeof(li));
    printf("\nTYPE: int NAME: \"sli\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", sli, LONG_MIN, LONG_MAX, sizeof(sli));
    printf("\nTYPE: int NAME: \"uli\" VALUE: %d MIN: %d MAX: %d BYTE: %d ", uli, LONG_MIN, ULONG_MAX, sizeof(uli));
    printf("\nTYPE: double NAME: \"ld\" VALUE: %f MIN: %f MAX: %e BYTE: %d \n", ld, LDBL_MIN, LDBL_MAX, sizeof(ld));

    return 0;
}
