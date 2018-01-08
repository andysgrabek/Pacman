//
// Created by Andrzej Grabowski on 29/12/2017.
//

#ifndef TASK8_PACMAN_PACMAN_CONSTANTS_H
#define TASK8_PACMAN_PACMAN_CONSTANTS_H

#define CUR_PATH "assets/"

#define CELL_WIDTH 25
#define GRAY_OFFSET 100
#define PINK_OFFSET 200
#define SMALL_DOTS 280
#define BIG_DOTS 8

#define GAME_TEXT "Arrows to steer, ESC to exit"
#define LOST_TEXT "You lost, ESC to exit, ENTER to restart"
#define WIN_TEXT "You won, ESC to exit, ENTER to restart"

#define FPS 40
#define DELAY (1000 / FPS)
#define MOUTH_CHANGE_INTERVAL 200
#define STANDARD_CELL column * CELL_WIDTH, row * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH
#define SMALL_DOT_CELL column * CELL_WIDTH + CELL_WIDTH / 2, row * CELL_WIDTH + CELL_WIDTH / 2, CELL_WIDTH / 8, CELL_WIDTH / 8
#define BIG_DOT_CELL column * CELL_WIDTH + CELL_WIDTH / 2 - CELL_WIDTH / 16, row * CELL_WIDTH + CELL_WIDTH / 2 - CELL_WIDTH / 16, CELL_WIDTH / 4, CELL_WIDTH / 4

#define LEFT_PAIR std::pair<short, short>(-1, 0)
#define RIGHT_PAIR std::pair<short, short>(1, 0)
#define UP_PAIR std::pair<short, short>(0, -1)
#define DOWN_PAIR std::pair<short, short>(0, 1)
#define DIRECTION_PAIRS { LEFT_PAIR, RIGHT_PAIR, UP_PAIR, DOWN_PAIR }
#define NONE_PAIR std::pair<short, short>(0, 0)

#define EXIT_SQUARE {350, 275}
#define BOARD_SIZE_X 725
#define BOARD_SIZE_Y 725

#define DEPLOY_TIME 3000
#define WAIT_TIME 1500
#define EAT_TIME 10000

enum COLOR {
    CYAN, PINK, RED, YELLOW
};

enum MODE {
    ATTACK, DEPLOY, RETREAT, RUN, EXIT
};

#endif //TASK8_PACMAN_PACMAN_CONSTANTS_H
