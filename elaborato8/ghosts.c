#define GHOSTS_STUD
#ifdef GHOSTS_STUD


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ghosts.h"
#include "pacman.h"
#include "matrix.h"
#include "global.h"

//dichiarazioni delle possibili direzioni
#define UP -1
#define DOWN +1
#define LEFT -1
#define RIGHT +1

typedef struct ghost
{
	struct position position;
	enum ghost_status status;
	unsigned int id;
} ghost;

typedef struct ghosts
{
	struct ghost* ghosts_array;
	unsigned int row;
	unsigned int column;
	char** arena;
	unsigned int ghost_count;
} ghosts;

static struct ghost* get_ghost_by_id(struct ghosts* G, unsigned int id) {
	int i;
	for (i = 0; i < G->ghost_count; i++) {
		if (G->ghosts_array[i].id == id)
			return &(G->ghosts_array[i]);
	}

	return NULL;
}

/* Create the ghosts data structure */
struct ghosts* ghosts_setup(unsigned int num_ghosts) {
	//creo in memoria la struttura 
	ghosts* g = (ghosts *)malloc(sizeof(ghosts));
	//se non riesco a mettere la struttura in memoria rompo l'esecuzione e libero la memoria
	if (g == NULL) {
		return NULL;
	}
	ghost* g_a = (ghost*)malloc(num_ghosts * sizeof(ghost));
	if (g_a == NULL)
	{
		free(g);
		return NULL;
	}
	g->row = 0;
	g->column = 0;
	g->ghost_count = num_ghosts;
	g->arena = NULL;
	g->ghosts_array = g_a;
	int i = 0;
	for (i; i < num_ghosts; i++) {
		g->ghosts_array[i].position.i = 0;
		g->ghosts_array[i].position.j = 0;
		g->ghosts_array[i].status = NORMAL;
		g->ghosts_array[i].id = i;
	}

	return g;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts* G) {
	int i;
	free(G->ghosts_array);
	G->ghosts_array = NULL;

	free(G);
	//G->ghost_count = ghosts_get_number(G) - 1;
	return;

}

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts* G, char** A, unsigned int nrow,
	unsigned int ncol) {
	G->arena = A;
	G->column = ncol;
	G->row = nrow;
	return;
}

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts* G, unsigned int id, struct position pos) {
	ghost* g = get_ghost_by_id(G, id);
	g->position = pos;
	return;
}

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts* G, unsigned int id, enum ghost_status status) {
	ghost* g = get_ghost_by_id(G, id);
	g->status = status;
	return;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts* G) {
	return G->ghost_count;
}

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts* G, unsigned int id) {
	struct position p;
	ghost* g = get_ghost_by_id(G, id);
	if (g != NULL)
		return g->position;
	else
		return (struct position) { 0, 0 };
}

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts* G, unsigned int id) {
	ghost* g = get_ghost_by_id(G, id);
	if (g != NULL)
		return g->status;
	else
		return 0;
}

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts* G, struct pacman* P, unsigned int id) {
	struct position p;
	ghost* g = get_ghost_by_id(G, id);
	struct position pacman_position = pacman_get_position(P);
	
	char** a = G->arena;

	switch (g->status) {
	case NORMAL:
		break;
	case SCARED_NORMAL:
		break;
	case SCARED_BLINKING:
		break;
	case EYES:
		break;
	}
	return p;
}

#endif


