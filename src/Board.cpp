#include "../include/Board.hpp"

Board::Board () {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            mGrid[y][x] = EMPTY_POS;
        }
    }
}

bool Board::isPosEmpty (int pX, int pY) {
    if (mGrid[pY][pX] == EMPTY_POS) {
        return true;
    }
    return false;
}

bool Board::isCollision (int pType, int pRotation, int pX, int pY) {
    for (int j = 0; j < PIECE_SIZE; j++) {
        for (int i = 0; i < PIECE_SIZE; i++) {

            if (PieceShapes[pType][pRotation][j][i] == EMPTY_BLOCK) {
                continue;
            }

            int gridX = pX + i;
            int gridY = pY + j;
            // 檢查是否超出左右邊界或底部
            if (gridX < 0 || gridX >= BOARD_WIDTH || gridY >= BOARD_HEIGHT) {
                return true;
            }
            // 檢查在棋盤範圍內是否與既有方塊重疊
            if (isPosEmpty (gridX, gridY) == false) {
                return true;
            }
        }
    }

    return false;
}

void Board::placeBlock (const Block& pBlock) {
    for (int j = 0; j < PIECE_SIZE; j++) {
        for (int i = 0; i < PIECE_SIZE; i++) {
            if (PieceShapes[pBlock.mType][pBlock.mRotation][j][i] == EMPTY_BLOCK) {
                continue;
            }

            int boardX = pBlock.mX + i;
            int boardY = pBlock.mY + j;
            
            mGrid[boardY][boardX] = FULL_POS;
        }
    }
}

int Board::clearLines () {
    int linesCleared = 0;

    for (int j = 0; j < BOARD_HEIGHT; j++) {
        bool isFullLine = true; // determine if the line is full;
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (mGrid[j][i] == EMPTY_POS) {
                isFullLine = false;
            }
        }

        // if it's full line, clear the line
        if (isFullLine) {
            clearLine (j);
            linesCleared++;
        }
    }

    return linesCleared;
}

void Board::clearLine (int pY) {
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mGrid[j][i] = mGrid[j - 1][i];
        }
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        mGrid[0][i] = EMPTY_POS;
    }
}

bool Board::isGameOver () {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mGrid[PIECE_SIZE][i] == FULL_POS) {
            return true;
        }
    }

    return false;
}

void Board::draw (const Block& currentBlock, int score) {
    // top
    std::cout << "+";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    std::cout << std::endl;
    // board
    for (int y = 1; y < BOARD_HEIGHT; y++) {
        std::cout << "|";
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (currentBlock.mX <= x && x < currentBlock.mX + PIECE_SIZE && currentBlock.mY <= y && y < currentBlock.mY + PIECE_SIZE) {
                if (mGrid[y][x] == FULL_POS) {
                    std::cout << "█";
                } else if (PieceShapes[currentBlock.mType][currentBlock.mRotation][y - currentBlock.mY][x - currentBlock.mX] == PIVOT_BLOCK) {
                    std::cout << "*";
                } else if (PieceShapes[currentBlock.mType][currentBlock.mRotation][y - currentBlock.mY][x - currentBlock.mX] == FULL_BLOCK) {
                    std::cout << "#";
                } else if (y == PIECE_SIZE) {
                    std::cout << "-";
                } else {
                    std::cout << " ";
                }
            } else {
                if (y == PIECE_SIZE && mGrid[y][x] == EMPTY_POS) {
                    std::cout << "-";
                } else if (mGrid[y][x] == EMPTY_POS) {
                    std::cout << " ";
                } else {
                    std::cout << "█";
                }
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    // underline
    std::cout << "+";
    for (int i = 0; i < BOARD_WIDTH; i++) { 
        std::cout << "-";
    }
    std::cout << "+";
    std::cout << std::endl;

    std::cout << "score: " << score << std::endl;
}