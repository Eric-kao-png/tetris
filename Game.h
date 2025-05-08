#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sys/select.h>
#include <chrono>

#define ONE_LINE_SCORE 10
#define TWO_LINE_SCORE 40
#define THREE_LINE_SCORE 100
#define FOUR_LINE_SCORE 400

class Game {
    private:
    
    Board mBoard;
    Block mBlock;
    bool mGameOver;
    int mScore;

    public:

    Game ();

    void spawnNewBlock ();
    void movePieceDown ();
    void movePieceLeft ();
    void movePieceRight ();
    void rotatePiece ();
    int calculateScore (int clearedLines);
    void run ();
    int getScore ();
};

#endif