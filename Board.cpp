#include "Board.h"

Board::Board () {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            mGrid[y][x] = 0;
        }
    }
}