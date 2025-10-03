//macro che aiuta la leggibilita' del codice
#define DELTA(a, b, c) (((b) * (b)) - 4 * (a) * (c))
//macro che cambia segno nel calcolo delle soluzioni: in questo modo im base al verso della parabola ritorno sempre il numero maggiore
#define DECIDE_SIGN(a) ((a) < 0 ? -1 : 1) //se a e' piu piccolo di zero cambio segno
//controllo il numero di soluzioni in base al delta
#define NUM_OF_ROOTS(a, b, c) DELTA(a, b, c) > 0 ? 2 : DELTA (a, b, c) == 0 ? 1 : 0
//macro che calcola la soluzione + grande di una equazione di secondo grado
#define ROOT1(a, b, c) (((-(b)) + DECIDE_SIGN(a) * sqrt(DELTA(a, b, c))) / (2 * (a))) 
//macro che calcola la soluzione + piccola di una equazione di secondo grado
#define ROOT2(a, b, c) (((-(b)) - DECIDE_SIGN(a) * sqrt(DELTA(a, b, c))) / (2 * (a)))
//dando per scontato che a != 0, il vertice della parabola sara' sempre un punto di massimo o minimo
#define EXTREME_POINT(a, b, c) ((-(b))/( 2 * (a))) 
//macro che "restituisce 0 se e' massimo o 1 se minimo"
#define MAXIMUM_POINT(a, b, c) ((a) > 0 ? 0 : 1)



