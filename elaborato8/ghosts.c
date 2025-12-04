	#define GHOSTS_STUD
	#ifdef GHOSTS_STUD


	#include <stdlib.h>
	#include <stdio.h>
	#include <time.h>
	#include "ghosts.h"
	#include "pacman.h"
	#include "matrix.h"
	#include "global.h"

	#define TRUE 1
	#define FALSE 0

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
		ghosts* g = (ghosts*)malloc(sizeof(ghosts));
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
	/*funzione di utility che sistema la posizione del fantasmino nel caso vada oltre l'arena*/
	//static void pacman_effect(struct position* p, unsigned int rows, unsigned int cols) {

	//	p->i = (p->i + rows) % rows;
	//	p->j = (p->j + cols) % cols;
	//}

	static int check_if_position_is_already_occupied(struct position p, struct ghosts* G, unsigned int my_ghost_id) {
		int loop_var;
		struct ghost* array = G->ghosts_array;

		for (loop_var = 0; loop_var < G->ghost_count; loop_var++) {
			if (array[loop_var].position.i == p.i && array[loop_var].position.j == p.j) {
				if (array[loop_var].id != my_ghost_id)
					return TRUE;
			}
		}
		return FALSE;
	}
	/* Move the ghost id (according to its status). Returns the new position */
	struct position ghosts_move(struct ghosts* G, struct pacman* P, unsigned int id) {
		struct position current_pos = ghosts_get_position(G, id);
		struct ghost* g = get_ghost_by_id(G, id);
		struct position pac_pos = pacman_get_position(P);
		struct position candidate_pos;
		struct position best_pos = current_pos;
		unsigned int rows = G->row;
		unsigned int cols = G->column;
		int possible_moves_i[] = { 1, -1, 0, 0 };
		int possible_moves_j[] = { 0, 0, 1, -1 };
		int loop_var = 0;
		long best_dist = -1;
		
		
		//se status e' eyes mi basta leggere il carattere nell'arena per tornare nella home
		if (g->status == EYES) {
			candidate_pos = current_pos;
			char dir_to_home = G->arena[current_pos.i][current_pos.j];
			int is_valid = 1;
			int move_i = 0;
			int move_j = 0;

			if (dir_to_home == 'U')      
				move_i = -1;
			else if (dir_to_home == 'D') 
				move_i = 1;
			else if (dir_to_home == 'R')
				move_j = 1;
			else                         
				move_j = -1;

			candidate_pos.i = ((int)current_pos.i + move_i + (int)rows) % (int)rows;
			candidate_pos.j = ((int)current_pos.j + move_j + (int)cols) % (int)cols;
			//pacman_effect(&candidate_pos, rows, cols);

			if (G->arena[candidate_pos.i][candidate_pos.j] == 'x')
			{
				is_valid = 0;
			}
			else if (check_if_position_is_already_occupied(candidate_pos, G, id) == 1)
			{
				is_valid = 0;
			}
			else if (candidate_pos.i == pac_pos.i && candidate_pos.j == pac_pos.j)
			{
				is_valid = 0;
			}

			if (is_valid)
			{
				g->position = candidate_pos;
				return candidate_pos;
			}
			else
			{
				return current_pos;
			}
		}
		/*se lo stato e' normal:
		-no muro
		-no altri fantasmi
		-vicino a pacman
		*/
		//visto che le mosso possibili sono solo 4, in questo modo posso fare un metodo iterativo

		
		for (loop_var = 0; loop_var < 4; loop_var++)
		{
			int is_valid = TRUE;
			int next_i = (int)current_pos.i + possible_moves_i[loop_var];
			int next_j = (int)current_pos.j + possible_moves_j[loop_var];

			candidate_pos.i = (next_i + (int)rows) % (int)rows;
			candidate_pos.j = (next_j + (int)cols) % (int)cols;
			
			//verifico che non vada oltre la grandezza massima dell'arena e nel caso sistemo
			/*pacman_effect(&candidate_pos, rows, cols);*/

			if (G->arena[candidate_pos.i][candidate_pos.j] == 'x' || check_if_position_is_already_occupied(candidate_pos, G, id) == TRUE)
			{
				is_valid = FALSE;
			}

			if (is_valid) {
				if (g->status != NORMAL) {
					if (candidate_pos.i == pac_pos.i && candidate_pos.j == pac_pos.j) {
						is_valid = FALSE;
					}
				}
			}

			if (is_valid) {
				//calcolo la distanza utilizzando il teorema di pitagora, tutto alla seconda in questo modo uso solo interi
				long diff_i = (long)candidate_pos.i - (long)pac_pos.i;
				long diff_j = (long)candidate_pos.j - (long)pac_pos.j;
				long root_dist = diff_i * diff_i + diff_j * diff_j;

				int is_better = FALSE;
				if (best_dist == -1) {
					is_better = TRUE;
				}
				else {
					if (g->status == NORMAL) {
						if (root_dist < best_dist) is_better = TRUE;
					}
					else {
						if (root_dist > best_dist) is_better = TRUE;
					}
				}

				if (is_better) {
					best_dist = root_dist;
					best_pos = candidate_pos;
				}
			}
		}

		g->position = best_pos;
		return best_pos;
	}

	#endif


