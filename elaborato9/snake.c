#include "snake.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct snake snake;
typedef struct body body;
typedef struct position position;

#define GO_UP(i, rows)     (((i) + (rows) - 1) % (rows))
#define GO_DOWN(i, rows)   (((i) + 1) % (rows))
#define GO_LEFT(j, cols)   (((j) + (cols) - 1) % (cols))
#define GO_RIGHT(j, cols)  (((j) + 1) % (cols)) 

static position calculate_new_position(position pos, enum direction dir, unsigned int rows, unsigned int cols) {
	position new_pos = pos;
	switch (dir) {
	case UP:
		new_pos.i = GO_UP(pos.i, rows);
		break;
	case DOWN:
		new_pos.i = GO_DOWN(pos.i, rows);
		break;
	case LEFT:
		new_pos.j = GO_LEFT(pos.j, cols);
		break;
	case RIGHT:
		new_pos.j = GO_RIGHT(pos.j, cols);
		break;
	}
	return new_pos;
}

static body* body_create(body* next, body* prev, position p) {
	body* b = (body*)calloc(1, sizeof(body));
	if (b == NULL)
		return NULL;
	b->next = next;
	b->prev = prev;
	b->pos = p;
	return b;
}
struct snake* snake_create(unsigned int rows, unsigned int cols) {
	position starting_pos;
	snake* s = (snake*)calloc(1, sizeof(snake));
	if (s == NULL)
		return NULL;
	s->cols = cols;
	s->rows = rows;
	s->length = 1;
	starting_pos;
	starting_pos.i = rows / 2;
	starting_pos.j = cols / 2;
	s->body = body_create(NULL, NULL, starting_pos);

	return s;
}

void snake_kill(struct snake* s) {
	body* next;
	body* current = s->body;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	free(s);
}

struct position snake_head(struct snake* s) {
	struct position p;
	if (s->body != NULL) {
		p = s->body->pos;
	}
	return p;

}

struct position snake_body(struct snake* s, unsigned int i) {
	struct position p;
	if (s == NULL || s->body == NULL) return;

	body* current = s->body;
	unsigned int k;
	for (k = 0; k < i; k++) {
		if (current->next == NULL) break;
		current = current->next;
	}

	if (current != NULL) {
		p = current->pos;
	}
	return p;
}

int snake_knotted(struct snake* s) {
	body* head = s->body;
	body* current = head;
	body* other;
	while (current != NULL) {
		other = current->next;
		while (other != NULL) {
			if (current->pos.i == other->pos.i && current->pos.j == other->pos.j) {
				return 1;
			}
			other = other->next;
		}
		current = other;
	}

	return 0;

}

void snake_move(struct snake* s, enum direction dir) {
	snake_increase(s, dir);
	snake_decrease(s, 1);
}

void snake_reverse(struct snake* s) {
	body* current = s->body;
	body* temp = NULL;
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp != NULL) {
		s->body = temp->prev;
	}
}

void snake_increase(struct snake* s, enum direction dir) {
	body* old_head = s->body;
	position new_head_pos = calculate_new_position(old_head->pos, dir, s->rows, s->cols);
	body* new_head = body_create(old_head, NULL, new_head_pos);
	if (old_head != NULL) {
		old_head->prev = new_head;
	}
	s->body = new_head;
	s->length++;
}

void snake_decrease(struct snake* s, unsigned int decrease_len) {
	body* tail;

	if (decrease_len == 0) {
		return;
	}
	tail = s->body;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	if (tail->prev != NULL) {
		tail->prev->next = NULL;
	}
	free(tail);
	s->length--;
	snake_decrease(s, decrease_len - 1);
}


/* Saves the snake into the filename. */
void snake_save(struct snake* s, char* filename) {
	body* current;
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		return;
	}
	fprintf(file, "%d\n", s->length);
	fprintf(file, "%d\n", s->rows);
	fprintf(file, "%d\n", s->cols);
	current = s->body;
	while (current != NULL) {
		fprintf(file, "%d\n %d\n", current->pos.i, current->pos.j);
		current = current->next;
	}
	fclose(file);
}

/* Loads the snake from filename */
struct snake* snake_read(char* filename) {
	unsigned int length, rows, cols;
	unsigned int* data;
	unsigned int i = 0;
	snake* read_snake;
	FILE* file = fopen(filename, "r");
	position head_pos;
	body* prev_body;
	position new_pos;
	body* new_body;

	if (file == NULL) return NULL;
	fscanf(file, "%d", &length);
	fscanf(file, "%d", &rows);
	fscanf(file, "%d", &cols);

	data = (unsigned int*)calloc(2 * length, sizeof(unsigned int));
	for (i; i < 2 * length; i++) {
		fscanf(file, "%d", &data[i]);
	}
	fclose(file);

	read_snake = snake_create(rows, cols);
	read_snake->length = length;
	free(read_snake->body); //devo liberare perche senno ho una posizione casuale
	head_pos.i = data[0];
	head_pos.j = data[1];
	read_snake->body = body_create(NULL, NULL, head_pos);
	prev_body = read_snake->body;
	for (i = 2; i < 2 * length; i += 2) {
		new_pos.i = data[i];
		new_pos.j = data[i + 1];
		new_body = body_create(NULL, prev_body, new_pos);
		prev_body->next = new_body;
		prev_body = new_body;
	}

	return read_snake;
}