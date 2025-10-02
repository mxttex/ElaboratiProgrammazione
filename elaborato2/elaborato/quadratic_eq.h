//controllo il numero di soluzioni in base al delta
#define NUM_OF_ROOTS(a, b, c) DELTA (a, b, c) > 0 ? 2 : DELTA (a, b, c) == 0 ? 1 : 0
#define ROOT1(a, b, c) ((-b + sqrt(DELTA(a, b, c))) / (2 * a))
#define ROOT2(a, b, c) ((-b - sqrt(DELTA(a, b, c))) / (2 * a))
#define EXTREME_POINT(a, b, c) //dando per scontato che a != 0, il vertice della parabola sara' sempre un punto di massimo o minimo
#define MAXIMUM(a, b, c)


//macro che aiuta la leggibilita' del codice
#define DELTA(a, b, c) (((b) * (b)) - (4 * (a) * (c)))