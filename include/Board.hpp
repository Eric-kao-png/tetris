#ifndef BOARD_H
#define BOARD_H

#include "../include/Piece.hpp"
#include <iostream>
#include <iomanip>
#include <array>

constexpr int BOARD_WIDTH = 8;
constexpr int BOARD_HEIGHT = 21;
constexpr int SHOW_NEXT_PIECE_TOP = 3;
constexpr int SHOW_NEXT_BLOCK_DISTANCE = 3;

enum class BoardBlock {empty, filled};

class Piece;

class Board {
    private:

    std::array< std::array<BoardBlock, BOARD_WIDTH> , BOARD_HEIGHT> mGrid;

    bool isEmptyBoardBlock (int pX, int pY) const;
    void clearLine (int pY); 

    public:

    Board ();

    bool isCollision (int pType, int pRotation, int pX, int pY) const; 
    void placePiece (const Piece& pPiece); 
    int checkLines (); 
    bool isGameOver () const; 
    void draw (const Piece& currentPiece, const Piece& PieceBottom, int nextPieceType, int score) const;
};

#endif // BOARD_H