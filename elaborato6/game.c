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


static void reset_ball_to_default_position(void) {
    game.ball_pos = game.default_ball_pos;
}

static void update_ball_position(void) {
    game.ball_pos.x += game.ball_dir.x;
    game.ball_pos.y += game.ball_dir.y;
}


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


struct position get_ball_pos(void) {
    return game.ball_pos;
}

struct position get_pad1_pos(void) {
    return game.pad1_pos;
}

struct position get_pad2_pos(void) {
    return game.pad2_pos;
}

unsigned int get_pad_len(void) {
    return game.pad_len;
}

void move_ball(void) {
    struct position ball_pos = get_ball_pos();
    struct position pad1_pos = get_pad1_pos();
    struct position pad2_pos = get_pad2_pos();
    unsigned int pad_len = get_pad_len();

    if (ball_pos.y == 0)
    {
        game.ball_dir.y = DOWN;
    }

    if (ball_pos.y == game.height)
    {
        game.ball_dir.y = UP;
    }


    if (ball_pos.x == 0) {
        pad2_score++;
        reset_ball_to_default_position();
        return;
    }

    if (ball_pos.x + 1 == game.width) {
        pad1_score++;
        reset_ball_to_default_position();
        return;
    }

    if (((pad1_pos.x == ball_pos.x) || (pad1_pos.x == ball_pos.x + 1)) && (pad1_pos.y == ball_pos.y + 1))
    {
        game.ball_dir.x = RIGHT;
        game.ball_dir.y = UP;
        update_ball_position();
        return;
    }

    if (((pad1_pos.x == ball_pos.x) || (pad1_pos.x == ball_pos.x + 1)) && (pad1_pos.y + pad_len) == ball_pos.y)
    {
        game.ball_dir.x = RIGHT;
        game.ball_dir.y = DOWN;
        update_ball_position();
        return;
    }

    if (((pad2_pos.x - ball_pos.x >= 0) && (pad2_pos.x - ball_pos.x <= 2)) && (pad2_pos.y - 1 == ball_pos.y))
    {
        game.ball_dir.x = LEFT;
        game.ball_dir.y = UP;
        update_ball_position();
        return;
    }

    if (((pad2_pos.x - ball_pos.x >= 0) && (pad2_pos.x - ball_pos.x <= 2)) && (pad2_pos.y + pad_len) == ball_pos.y)
    {
        game.ball_dir.x = LEFT;
        game.ball_dir.y = DOWN;
        update_ball_position();
        return;
    }

    if (ball_pos.y >= pad1_pos.y &&
        ball_pos.y <= (pad1_pos.y + pad_len) &&
        (pad1_pos.x == (ball_pos.x - 1)))
    {
        game.ball_dir.x = RIGHT;
        update_ball_position();
        return;
    }

    if (ball_pos.y >= pad2_pos.y &&
        ball_pos.y <= (pad2_pos.y + pad_len) &&
        (pad2_pos.x == (ball_pos.x + 2)))
    {
        game.ball_dir.x = LEFT;
        update_ball_position();
        return;
    }

    update_ball_position();

}

void move_pad1_up(void) {
    struct position pad1_pos = get_pad1_pos();
    struct position ball_pos = get_ball_pos();

    if (pad1_pos.y == 0) {
        return;
    }

    if (((pad1_pos.x == ball_pos.x) || (pad1_pos.x == ball_pos.x + 1)) && (pad1_pos.y == ball_pos.y + 1))
    {
        return;
    }
    game.pad1_pos.y += UP;
}

void move_pad2_up(void) {
    struct position pad2_pos = get_pad2_pos();
    struct position ball_pos = get_ball_pos();

    if (pad2_pos.y == 0) {
        return;
    }

    if (((pad2_pos.x - ball_pos.x >= 0) && (pad2_pos.x - ball_pos.x <= 2)) && (pad2_pos.y - 1 == ball_pos.y))
    {
        return;
    }
    game.pad2_pos.y += UP;
}

void move_pad1_down(void) {
    struct position pad1_pos = get_pad1_pos();
    struct position ball_pos = get_ball_pos();
    unsigned int pad_len = get_pad_len();

    if ((pad1_pos.y + pad_len - 1) == game.height) {
        return;
    }

    if (((pad1_pos.x == ball_pos.x) || (pad1_pos.x == ball_pos.x + 1)) && (pad1_pos.y + pad_len) == ball_pos.y)
    {
        return;
    }
    game.pad1_pos.y += DOWN;
}

void move_pad2_down(void) {
    struct position pad2_pos = get_pad2_pos();
    struct position ball_pos = get_ball_pos();
    unsigned int pad_len = get_pad_len();

    if ((pad2_pos.y + pad_len - 1) == game.height) {
        return;
    }

    if (((pad2_pos.x - ball_pos.x >= 0) && (pad2_pos.x - ball_pos.x <= 2)) && (pad2_pos.y + pad_len) == ball_pos.y)
    {
        return;
    }
    game.pad2_pos.y += DOWN;
}

unsigned int get_pad1_score(void) {
    return pad1_score;
}

unsigned int get_pad2_score(void) {
    return pad2_score;
}