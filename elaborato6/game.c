#define STUD
#ifdef STUD

#include"game.h"
#define TRUE 0
#define FALSE 1
#define LEFT  -1
#define RIGHT  1
#define UP     -1
#define DOWN   1
/*
 * Setup a game with the following starting configuration:
 * - table dimension equal to heigth*width
 * - ball starting position at ball_pos
 * - ball starting direction towards ball_dir
 * - pad1 starting position at pad1_pos
 * - pad2 starting position at pad2_pos
 * - pad length equal to pad_len
 */

static unsigned int pad1_score;
static unsigned int pad2_score;

struct Game
{
	int height;
	int width;
	struct position ball_pos;
	struct position ball_dir;
	struct position pad1_pos;
	struct position pad2_pos;
	struct position default_ball_pos;
	int pad_len;

} game;

void setup_game(int height, int width,
	struct position ball_pos, struct position ball_dir,
	struct position pad1_pos, struct position pad2_pos, int pad_len) {
	// Implementation of game setup
	game.height = height;
	game.width = width;
	game.ball_pos = ball_pos;
	game.ball_dir = ball_dir;
	game.pad1_pos = pad1_pos;
	game.pad2_pos = pad2_pos;
	game.pad_len = pad_len;
	game.default_ball_pos = ball_pos;
	pad1_score = 0;
	pad2_score = 0;

}

static void reset_ball_to_center() {
	game.ball_pos = game.default_ball_pos;
}

static int pad_out_of_border(struct position p) {
	unsigned int pad_len = get_pad_len();
	if (p.y < 0) return TRUE;
	if (p.y + (int)pad_len >= game.height) return TRUE;
	return FALSE;
}
static int deny_pad_movement_if_ball_touches_edges(struct position pad_pos, struct position ball_pos)
{
	unsigned int pad_len;
	pad_len = get_pad_len();
	if (ball_pos.x == pad_pos.x || ball_pos.x + 1 == pad_pos.x) {
		if (ball_pos.y == pad_pos.y - 1) return TRUE;
		if (ball_pos.y == pad_pos.y + pad_len) return TRUE;
	}
	return FALSE;
}


static struct position check_collision(struct position p) {
	struct position pad_pos1 = get_pad1_pos();
	struct position pad_pos2 = get_pad2_pos();
	unsigned int pad_len = get_pad_len();
	struct position newDirection = game.ball_dir;

	if (p.y <= 0) {
		newDirection.y = DOWN;
	}
	else if (p.y >= game.height - 1) {
		newDirection.y = UP;
	}

	if (p.x == pad_pos1.x + 1) {
		if (p.y == pad_pos1.y - 1) {
			newDirection.x = RIGHT;
			newDirection.y = DOWN;
		}
		else if (p.y == pad_pos1.y + pad_len) {
			newDirection.x = RIGHT;
			newDirection.y = UP;
		}
		else if (p.y >= pad_pos1.y && p.y < pad_pos1.y + (int)pad_len) {
			newDirection.x = RIGHT;
		}
	}
	else if (p.x == pad_pos2.x - 1) {
		if (p.y == pad_pos2.y - 1) {
			newDirection.x = LEFT;
			newDirection.y = DOWN;
		}
		else if (p.y == pad_pos2.y + pad_len) {
			newDirection.x = LEFT;
			newDirection.y = UP;
		}
		else if (p.y >= pad_pos2.y && p.y < pad_pos2.y + (int)pad_len) {
			newDirection.x = LEFT;
		}
	}



	return newDirection;
}

struct position get_ball_dir(void) {
	// Implementation of getting ball direction
	return game.ball_dir;
}

void move_ball(void) {
	struct position ball_pos = get_ball_pos();
	struct position dir = get_ball_dir();
	struct position next_pos;

	next_pos.x = ball_pos.x + dir.x;
	next_pos.y = ball_pos.y + dir.y;

	if (next_pos.x <= 0) {
		reset_ball_to_center();
		pad2_score++;
		return;
	}
	else if (next_pos.x >= game.width - 1) {
		reset_ball_to_center();
		pad1_score++;
		return;
	}

	game.ball_dir = check_collision(next_pos);

	game.ball_pos.x = ball_pos.x + game.ball_dir.x;
	game.ball_pos.y = ball_pos.y + game.ball_dir.y;
}

void move_pad1_up(void) {
	// Implementation of moving pad1 up
	struct position newPos = get_pad1_pos();
	newPos.y = newPos.y + UP;
	if (pad_out_of_border(newPos) == FALSE && deny_pad_movement_if_ball_touches_edges(newPos, get_ball_pos()) == FALSE)
	{
		game.pad1_pos = newPos;
	}
}
void move_pad1_down(void) {
	// Implementation of moving pad1 down
	struct position newPos = get_pad1_pos();
	newPos.y = newPos.y + DOWN;
	if (pad_out_of_border(newPos) == FALSE && deny_pad_movement_if_ball_touches_edges(newPos, get_ball_pos()) == FALSE)
	{
		game.pad1_pos = newPos;
	}
}
void move_pad2_up(void) {
	// Implementation of moving pad2 up
	struct position newPos = get_pad2_pos();
	newPos.y = newPos.y + UP;
	if (pad_out_of_border(newPos) == FALSE && deny_pad_movement_if_ball_touches_edges(newPos, get_ball_pos()) == FALSE)
	{
		game.pad2_pos = newPos;
	}
}
void move_pad2_down(void) {
	// Implementation of moving pad2 down
	struct position newPos = get_pad2_pos();
	newPos.y = newPos.y + DOWN;
	if (pad_out_of_border(newPos) == FALSE && deny_pad_movement_if_ball_touches_edges(newPos, get_ball_pos()) == FALSE)
	{
		game.pad2_pos = newPos;
	}
}
struct position get_pad1_pos(void) {
	// Implementation of getting pad1 position
	return game.pad1_pos;
}

struct position get_pad2_pos(void) {
	// implementation of getting pad2 position
	return game.pad2_pos;
}
struct position get_ball_pos(void) {
	// Implementation of getting ball position
	return game.ball_pos;
}

unsigned int get_pad_len(void) {
	// Implementation of getting pad length
	return game.pad_len;
}
unsigned int get_pad1_score(void) {
	// Implementation of getting pad1 score
	return pad1_score;
}
unsigned int get_pad2_score(void) {
	// Implementation of getting pad2 score
	return pad2_score;

}

#endif