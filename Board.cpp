#include "Board.h"

Board::Board () {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            mGrid[y][x] = 0;
        }
    }
}

bool Board::isCellEmpty (int pX, int pY) {
    if (mGrid[pY][pX] == 1) {
        return true;
    }
    return false;
}

bool Board::isCollision (int pType, int pRotation, int pX, int pY) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (shapes[pType][pRotation][j][i] != 0) {
                int boardX = pX + i, boardY = pY + j;
                // 檢查是否超出左右邊界或底部
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT) {
                    return true;
                }
                // 檢查在棋盤範圍內是否與既有方塊重疊
                if (boardY >= 0 && mGrid[boardY][boardX] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::placeBlock (const Block& pBlock) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (shapes[pBlock.mType][pBlock.mRotation][j][i] == 0) {
                continue;
            }

            int boardX = pBlock.mX + i, boardY = pBlock.mY + j;

            if (boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT) {
                continue;
            }
            
            mGrid[boardY][boardX] = 1;
        }
    }
}

int Board::checkLines () {
    int linesCleared = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        bool fullLine = true; // determine if the line is full;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (mGrid[i][j] == 0) {
                fullLine = false;
            }
        }

        // if it's full line, clear the line
        if (fullLine) {
            clearLine (i);
            linesCleared++;
        }
    }

    return linesCleared;
}

void Board::clearLine (int pY) {
    for (int i = pY; i >= 1; i--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            mGrid[i][j] = mGrid[i - 1][j];
        }
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        mGrid[0][i] = 0;
    }
}

bool Board::isGameOver () {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mGrid[0][i] != 0) {
            return true;
        }
    }

    return false;
}

void Board::draw (const Block& currentBlock) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        std::cout << "|"; // lift board
        for (int x = 0; x < BOARD_WIDTH; x++) { // game console

            bool isFilled = false;
            for (int j = 0; j < BLOCK_SIZE; j++) {
                for (int i = 0; i < BLOCK_SIZE; i++) {
                    if (shapes[j][i] != 0) {
                        int boardX = currentBlock.mX + i;
                        int boardY = currentBlock.mY + j;
                        if (boardX == x && boardY == y) {
                            isFilled = true;
                        }
                    }
                }
            }
            
            if (isFilled || mGrid[y][x] == 1) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|"; // right board
        std::cout << std::endl;
    }

    for (int i = 0; i < BOARD_WIDTH + 2; i++) { // underline
        std::cout << "=";
    }
}