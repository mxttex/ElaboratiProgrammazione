#include<stdio.h>
#include<limits.h>
#include<float.h>

void main() {
    /*dichiarazione e assegnazione variabili, una ciascuna per ogni tipo e modificatore*/
    char c = 'c';
    int i = 10;
    float f = 3.14;
    double d = 5.5;
    signed char sc = -10;
    unsigned char uc = 3;
    signed int si = -67;
    unsigned int ui = 17;
    short int shi = 1;
    signed short int ssi = -255;
    unsigned short int usi = 254;
    long int li = 1000;
    signed long int sli = -1234;
    unsigned long int uli = 4687935;
    long double ld = 7.568;

    /*stampa a console per ogni variabile, seguendo il formato:
    TYPE: char NAME: c VALUE: x MIN: -128 MAX: 127 BYTE: 1
    */
    printf("TYPE %-15sNAME %-15sVALUE %-15sMIN %-15sMAX %-15sBYTE\n", "", "", "", "", "");
    
    //CHAR
    printf("%-19s %-20s", "char", "\"c\"");
    printf("%-21c", c);
    printf("%-19d", CHAR_MIN);
    printf("%-19d", CHAR_MAX);
    printf("%u\n", sizeof(c));
    //SIGNED CHAR
    printf("%-19s %-20s", "signed char", "\"sc\"");
    printf("%-21d", sc);
    printf("%-19d", SCHAR_MIN);
    printf("%-19d", SCHAR_MAX);
    printf("%u\n", sizeof(sc));
    //UNSIGNED CHAR
    printf("%-19s %-20s", "unsigned char", "\"uc\"");
    printf("%-21d", uc);
    printf("%-19d", 0);
    printf("%-19u", UCHAR_MAX);
    printf("%u\n", sizeof(uc));
    //INT
    printf("%-19s %-20s", "int", "\"i\"");
    printf("%-21d", i);
    printf("%-19d", INT_MIN);
    printf("%-19d", INT_MAX);
    printf("%u\n", sizeof(i));
    //SIGNED INT
    printf("%-19s %-20s", "signed int", "\"si\"");
    printf("%-21d", si);    
    printf("%-19d", INT_MIN);
    printf("%-19d", INT_MAX);
    printf("%u\n", sizeof(si));
    //UNSIGNED INT
    printf("%-19s %-20s", "unsigned int", "\"ui\"");
    printf("%-21d", ui);
    printf("%-19d", 0);
    printf("%-19u", UINT_MAX);
    printf("%u\n", sizeof(ui));
    //SHORT INT
    printf("%-19s %-20s", "short int", "\"shi\"");
    printf("%-21hd", shi);
    printf("%-19d", SHRT_MIN);
    printf("%-19d", SHRT_MAX);
    printf("%u\n", sizeof(shi));
    //SIGNED SHORT INT
    printf("%-19s %-20s", "signed short int", "\"ssi\"");
    printf("%-21hd", ssi);
    printf("%-19d", SHRT_MIN);
    printf("%-19d", SHRT_MAX);
    printf("%u\n", sizeof(ssi));
    //UNSIGNED SHORT INT
    printf("%-19s %-20s", "unsigned short int", "\"usi\"");
    printf("%-21hu", usi);
    printf("%-19d", 0);
    printf("%-19u", USHRT_MAX);
    printf("%u\n", sizeof(usi));
    //LONG INT
    printf("%-19s %-20s", "long int", "\"li\"");
    printf("%-21ld", li);
    printf("%-19d", LONG_MIN);
    printf("%-19d", LONG_MAX);
    printf("%u\n", sizeof(li));
    //SIGNED LONG INT
    printf("%-19s %-20s", "signed long int", "\"sli\"");
    printf("%-21ld", sli);
    printf("%-19d", LONG_MIN);
    printf("%-19d", LONG_MAX);
    printf("%u\n", sizeof(sli));
    //UNSIGNED LONG INT
    printf("%-19s %-20s", "unsigned long int", "\"uli\"");
    printf("%-21lu", uli);
    printf("%-19d", 0);
    printf("%-19u", ULONG_MAX);
    printf("%u\n", sizeof(uli));
    //FLOAT
    printf("%-19s %-20s", "float", "\"f\"");
    printf("%-21f", f);
    printf("%-19e", FLT_MIN);
    printf("%-19e", FLT_MAX);
    printf("%u\n", sizeof(f));
    //DOUBLE
    printf("%-19s %-20s", "double", "\"d\"");
    printf("%-21f", d);
    printf("%-19e", DBL_MIN);
    printf("%-19e", DBL_MAX);
    printf("%u\n", sizeof(d));
    //LONG DOUBLE
    printf("%-19s %-20s", "long double", "\"ld\"");
    printf("%-21lf", ld);
    printf("%-19e", LDBL_MIN);
    printf("%-19e", LDBL_MAX);
    printf("%u\n", sizeof(ld));
 
    return 0;
}

