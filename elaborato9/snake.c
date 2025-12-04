#include "snake.h" 
#include <stdio.h>
#include <stdlib.h>

typedef struct snake snake;
typedef struct body body;
typedef struct position position;

static body* body_create(body* next, body* prev, position p) {
	body* b = (body*)malloc(sizeof(body));
	if (b == NULL)
		return NULL;
	b->next = next;
	b->prev = prev;
	b->pos = p;
	return b;
}
struct snake* snake_create(unsigned int rows, unsigned int cols) {
	snake* s = (snake *)malloc(sizeof(snake));
	if (s == NULL)
		return NULL;
	s->cols = cols;
	s->rows = rows;
	s->length = 1;
	position starting_pos;
	starting_pos.i = rows / 2;
	starting_pos.j = cols / 2;
	body_create(NULL, NULL, starting_pos);

	return s;
}

void snake_kill(struct snake* s) {
	
	free(s);
}

struct position snake_head(struct snake* s) {
	struct position p;
	return p;

}

struct position snake_body(struct snake* s, unsigned int i) {
	struct position p;
	return p;
}

int snake_knotted(struct snake* s) {
	return 0;
}

void snake_move(struct snake* s, enum direction dir) {
}

void snake_reverse(struct snake* s) {
}

void snake_increase(struct snake* s, enum direction dir) {
}

void snake_decrease(struct snake* s, unsigned int decrease_len) {
}


/* Saves the snake into the filename. */
void snake_save(struct snake* s, char* filename) {

}

/* Loads the snake from filename */
struct snake* snake_read(char* filename) {
	return NULL;
}
