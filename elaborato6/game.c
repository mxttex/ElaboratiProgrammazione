
#include "game.h"

#define TRUE 1
#define FALSE 0
#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1

static unsigned int pad1_score;
static unsigned int pad2_score;

struct Game {
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

static void reset_ball_to_center(void) {
    game.ball_pos = game.default_ball_pos;
}

static int pad_out_of_border(struct position p) {
    unsigned int pad_len = get_pad_len();

    if (p.y < 0)
        return TRUE;
    if (p.y + pad_len - 1 > game.height)
        return TRUE;

    return FALSE;
}

static int deny_pad_movement_if_ball_touches_edges(struct position actual_pad_pos, int direction) {
    unsigned int pad_len = get_pad_len();
    struct position ball_pos = get_ball_pos();

    if (ball_pos.x == actual_pad_pos.x || ball_pos.x + 1 == actual_pad_pos.x || ball_pos.x - 1 == actual_pad_pos.x) {
        if (direction == UP && ball_pos.y == actual_pad_pos.y - 1)
            return TRUE;
        if (direction == DOWN && ball_pos.y == actual_pad_pos.y + pad_len)
            return TRUE;
    }
    return FALSE;
}

static struct position check_collision(struct position p) {

    struct position pad_pos1;
    struct position pad_pos2;
    unsigned int pad_len;
    struct position newDirection;

    pad_pos1 = get_pad1_pos();
    pad_pos2 = get_pad2_pos();
    pad_len = get_pad_len();

    newDirection = game.ball_dir;

    if (p.x <= pad_pos1.x) {
        if (p.y >= pad_pos1.y && p.y < (pad_pos1.y + pad_len)) {
            newDirection.x = RIGHT;
        }
        else if (p.y == pad_pos1.y - 1) {
            newDirection.x = RIGHT;
            newDirection.y = UP;
        }
        else if (p.y == pad_pos1.y + pad_len) {
            newDirection.x = RIGHT;
            newDirection.y = DOWN;
        }
    }
    else if (p.x + 1 == pad_pos2.x) {
        if (p.y >= pad_pos2.y && p.y < (pad_pos2.y + pad_len)) {
            newDirection.x = LEFT;
        }
        else if (p.y == pad_pos2.y - 1) {
            newDirection.x = LEFT;
            newDirection.y = UP;
        }
        else if (p.y == pad_pos2.y + pad_len) {
            newDirection.x = LEFT;
            newDirection.y = DOWN;
        }
    }

    if (p.y + 1 == 0) {
        newDirection.y = DOWN;
    }
    else if (p.y - 1 == game.height) {
        newDirection.y = UP;
    }

    return newDirection;
}

struct position get_ball_dir(void) {
    return game.ball_dir;
}

void move_ball(void) {
    struct position ball_pos;
    struct position current_dir;
    struct position next_pos;
    struct position new_dir;

    ball_pos = get_ball_pos();
    current_dir = get_ball_dir();

    next_pos.x = ball_pos.x + current_dir.x;
    next_pos.y = ball_pos.y + current_dir.y;

    if (next_pos.x - 1 <= 0) {
        reset_ball_to_center();
        pad2_score++;
        return;
    }
    else if (next_pos.x >= game.width) {
        reset_ball_to_center();
        pad1_score++;
        return;
    }
    new_dir = check_collision(next_pos);

    game.ball_pos.x = ball_pos.x + new_dir.x;
    game.ball_pos.y = ball_pos.y + new_dir.y;
    game.ball_dir = new_dir;
}

void move_pad1_up(void) {
    struct position actualPos = get_pad1_pos();
    struct position newPos = actualPos;
    newPos.y = newPos.y + UP;
    if (pad_out_of_border(newPos) == FALSE &&
        deny_pad_movement_if_ball_touches_edges(actualPos, UP) == FALSE)
        game.pad1_pos = newPos;
}

void move_pad1_down(void) {
    struct position actualPos = get_pad1_pos();
    struct position newPos = actualPos;
    newPos.y = newPos.y + DOWN;

    if (pad_out_of_border(newPos) == FALSE &&
        deny_pad_movement_if_ball_touches_edges(actualPos, DOWN) == FALSE)
        game.pad1_pos = newPos;
}

void move_pad2_up(void) {
    struct position actualPos = get_pad2_pos();
    struct position newPos = actualPos;
    newPos.y = newPos.y + UP;

    if (pad_out_of_border(newPos) == FALSE &&
        deny_pad_movement_if_ball_touches_edges(actualPos, UP) == FALSE)
        game.pad2_pos = newPos;
}

void move_pad2_down(void) {
    struct position actualPos = get_pad2_pos();
    struct position newPos = actualPos;
    newPos.y = newPos.y + DOWN;

    if (pad_out_of_border(newPos) == FALSE &&
        deny_pad_movement_if_ball_touches_edges(actualPos, DOWN) == FALSE)
        game.pad2_pos = newPos;
}

struct position get_pad1_pos(void) {
    return game.pad1_pos;
}

struct position get_pad2_pos(void) {
    return game.pad2_pos;
}

struct position get_ball_pos(void) {
    return game.ball_pos;
}

unsigned int get_pad_len(void) {
    return game.pad_len;
}

unsigned int get_pad1_score(void) {
    return pad1_score;
}

unsigned int get_pad2_score(void) {
    return pad2_score;
}

