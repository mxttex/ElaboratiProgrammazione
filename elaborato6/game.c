#include"game.h"
/*
 * Setup a game with the following starting configuration:
 * - table dimension equal to heigth*width
 * - ball starting position at ball_pos
 * - ball starting direction towards ball_dir
 * - pad1 starting position at pad1_pos
 * - pad2 starting position at pad2_pos
 * - pad length equal to pad_len
 */
void setup_game(int height, int width,
		   struct position ball_pos, struct position ball_dir,
		   struct position pad1_pos, struct position pad2_pos, int pad_len) {
	// Implementation of game setup
}
void move_ball(void) {
	// Implementation of ball movement
}
void move_pad1_up(void) {
	// Implementation of moving pad1 up
}
void move_pad1_down(void) {
	// Implementation of moving pad1 down
}
void move_pad2_up(void) {
	// Implementation of moving pad2 up
}
void move_pad2_down(void) {
	// Implementation of moving pad2 down
}
struct position get_pad1_pos(void) {
	// Implementation of getting pad1 position
}

struct position get_pad2_pos(void) {
	// implementation of getting pad2 position
}
struct position get_ball_pos(void) {
	// Implementation of getting ball position
}	

unsigned int get_pad_len(void) {
	// Implementation of getting pad length
}
unsigned int get_pad1_score(void) {
	// Implementation of getting pad1 score
}
unsigned int get_pad2_score(void) {
	// Implementation of getting pad2 score
}
