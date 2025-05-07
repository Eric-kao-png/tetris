#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sys/select.h>

class Game {
    private:
    
    Board mBoard;
    Block mBlock;
    bool mGameOver;

    public:

    Game ();

    void spawnNewBlock ();
    void movePieceDown ();
    void movePieceLeft ();
    void movePieceRight ();
    void rotatePiece ();
    bool isGameOver ();
    void loop ();
};

#endif