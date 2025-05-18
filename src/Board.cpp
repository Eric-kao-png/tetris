#include "../include/Board.hpp"

Board::Board () {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        mGrid.at(y).fill(BoardBlock::empty);
    }
}

bool Board::isEmptyBoardBlock (int pX, int pY) const {
    if (mGrid.at(pY).at(pX) == BoardBlock::empty) {
        return true;
    }
    return false;
}

bool Board::isCollision (int pType, int pRotation, int pX, int pY) const {
    for (int j = 0; j < PIECE_SIZE; j++) {
        for (int i = 0; i < PIECE_SIZE; i++) {

            if (PieceShapes[pType][pRotation][j][i] == static_cast<int> (PieceBlock::empty)) {
                continue;
            }

            int gridX = pX + i;
            int gridY = pY + j;
            
            if (gridX < 0 || gridX >= BOARD_WIDTH || gridY >= BOARD_HEIGHT) {
                return true;
            }
            
            if (isEmptyBoardBlock (gridX, gridY) == false) {
                return true;
            }
        }
    }

    return false;
}

void Board::placePiece (const Piece& pPiece) {
    for (int j = 0; j < PIECE_SIZE; j++) {
        for (int i = 0; i < PIECE_SIZE; i++) {

            if (PieceShapes[pPiece.getType()][pPiece.getRotation()][j][i] == static_cast<int> (PieceBlock::empty)) {
                continue;
            }

            int boardX = pPiece.getX() + i;
            int boardY = pPiece.getY() + j;
            
            mGrid.at(boardY).at(boardX) = BoardBlock::filled;
        }
    }
}

int Board::checkLines () {
    int linesCleared = 0;

    for (int j = 0; j < BOARD_HEIGHT; j++) {
        bool isFullLine = true; 
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (mGrid.at(j).at(i) == BoardBlock::empty) {
                isFullLine = false;
            }
        }

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
            mGrid.at(j).at(i) = mGrid.at(j - 1).at(i);
        }
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        mGrid.at(0).at(i) = BoardBlock::empty;
    }
}

bool Board::isGameOver () const {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mGrid.at(PIECE_SIZE).at(i) == BoardBlock::filled) {
            return true;
        }
    }
    return false;
}

void Board::draw (const Piece& currentPiece, const Piece& PieceBottom, int nextPieceType, int score) const {
    // top
    std::cout << "+";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    std::cout << std::endl;
    // board
    for (int j = 1; j < BOARD_HEIGHT; j++) {
        std::cout << "|";
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (currentPiece.getX() <= i && i < currentPiece.getX() + PIECE_SIZE && currentPiece.getY() <= j && j < currentPiece.getY() + PIECE_SIZE) {
                if (mGrid.at(j).at(i) == BoardBlock::filled) {
                    std::cout << "█";
                } else if (PieceShapes[currentPiece.getType()][currentPiece.getRotation()][j - currentPiece.getY()][i - currentPiece.getX()] == static_cast<int> (PieceBlock::pivot)) {
                    std::cout << "*";
                } else if (PieceShapes[currentPiece.getType()][currentPiece.getRotation()][j - currentPiece.getY()][i - currentPiece.getX()] == static_cast<int> (PieceBlock::filled)) {
                    std::cout << "#";
                } else if (j == PIECE_SIZE) {
                    std::cout << "-";
                } else {
                    std::cout << " ";
                }
            } else if (PieceBottom.getY() - currentPiece.getY() > 5 && PieceBottom.getX() <= i && i < PieceBottom.getX() + PIECE_SIZE && PieceBottom.getY() <= j && j < PieceBottom.getY() + PIECE_SIZE) {
                if (mGrid.at(j).at(i) == BoardBlock::filled) {
                    std::cout << "█";
                } else if (PieceShapes[PieceBottom.getType()][PieceBottom.getRotation()][j - PieceBottom.getY()][i - PieceBottom.getX()] != static_cast<int> (PieceBlock::empty)) {
                    std::cout << "⎕";
                } else {
                    std::cout << " ";
                }
            } else {
                if (mGrid.at(j).at(i) == BoardBlock::filled) {
                    std::cout << "█";
                } else if (j == PIECE_SIZE && mGrid.at(j).at(i) == BoardBlock::empty) {
                    std::cout << "-";
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << "|";

        if (j >= SHOW_NEXT_PIECE_TOP && j <= SHOW_NEXT_PIECE_TOP + PIECE_SIZE - 1) {
            std::cout << std::setw(SHOW_NEXT_BLOCK_DISTANCE);
            for (int i = 0; i < PIECE_SIZE; i++) {
                if (PieceShapes[nextPieceType][0][j - SHOW_NEXT_PIECE_TOP][i] == static_cast<int> (PieceBlock::empty)) {
                    std::cout << " ";
                }
                if (PieceShapes[nextPieceType][0][j - SHOW_NEXT_PIECE_TOP][i] == static_cast<int> (PieceBlock::filled)) {
                    std::cout << "#";
                }
                if (PieceShapes[nextPieceType][0][j - SHOW_NEXT_PIECE_TOP][i] == static_cast<int> (PieceBlock::pivot)) {
                    std::cout << "*";
                }
            }
        }
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