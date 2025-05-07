#include "Game.h"

Game::Game () : mGameOver(false), mBlock(Block(0)) {
    srand (static_cast<unsigned int> (std::time (nullptr)));
    spawnNewBlock ();
}

void Game::spawnNewBlock () {
    int newType = rand() % 7;
    mBlock.mType = newType;
    mBlock.mRotation = 0;
    mBlock.mX = BOARD_WIDTH / 2 - BLOCK_SIZE / 2;
    mBlock.mY = 0;

    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
        mGameOver = true;
    }
}

void Game::movePieceDown () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY + 1)) {
        mBlock.mY += 1;
    } else {
        mBoard.placeBlock (mBlock);
        mBoard.checkLines();
        spawnNewBlock();
    }
}

void Game::movePieceLeft () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX - 1, mBlock.mY)) {
        mBlock.mX -= 1;
    }
}

void Game::movePieceRight () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX + 1, mBlock.mY)) {
        mBlock.mX += 1;
    }
}

void Game::rotatePiece () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
        if (mBlock.mRotation == 3) {
            mBlock.mRotation = 0;
        } else {
            mBlock.mRotation += 1;
        }   
    }
}

bool Game::isGameOver () {
    return mGameOver;
}

void Game::loop () {
    while (!mGameOver) {
        system("clear");
        mBoard.draw(mBlock); // 繪製目前棋盤和方塊

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval tv = {1, 0};
        int retval = select (STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

        if (retval > 0 && FD_ISSET (STDIN_FILENO, &readfds)) {
            char input = 0;
            if (read (STDIN_FILENO, &input, 1) > 0) {
                if (input == 'q') {
                    mGameOver = true;
                    break;
                }
                if (input == 'a') {
                    movePieceLeft();
                    continue;
                }
                if (input == 'd') {
                    movePieceRight();
                    continue;
                }
                if (input == 's') {
                    movePieceDown();
                    continue;
                }
                if (input == 'w') {
                    rotatePiece();
                    continue;
                }
            }
        }

        movePieceDown();
    }

    if (mGameOver) {
        system("clear");
        mBoard.draw(mBlock);
        std::cout << "game over!" << std::endl;
    }
}