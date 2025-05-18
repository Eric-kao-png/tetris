#ifndef GAME_H
#define GAME_H

#include "../include/Board.hpp"
#include "../include/Piece.hpp"
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sys/select.h>
#include <chrono>

constexpr int ONE_LINE_SCORE = 10;
constexpr int TWO_LINE_SCORE = 40;
constexpr int THREE_LINE_SCORE = 100;
constexpr int FOUR_LINE_SCORE = 400;

class Game {
    private:
    
    Board mBoard;
    Piece mPiece;
    Piece mPieceBottom;
    int mNextPieceType;
    bool mGameOver;
    int mScore;

    int calculateScore (int clearedLines);
    void spawnNewBlock ();
    int determineNextPiece ();
    void movePieceBottom ();
    bool checkCollision ();
    void clearAndDraw ();
    char receiveInput ();
    void processInput (char input);

    public:

    Game ();

    int getScore () const {return mScore;}
    void run ();
};

#endif // GAME_H