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
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
        mBlock.mY -= 1;
    } else {
        mBoard.placeBlock (mBlock);
        mBoard.checkLines();
        spawnNewBlock();
    }
}

void Game::movePieceLeft () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
        mBlock.mX -= 1;
    }
}

void Game::movePieceRight () {
    if (!mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
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
    int tick = 0;
    const int tickThreshold = 10; // 每10個迴圈觸發一次自動下落
    while (!mGameOver) {
        system("clear");
        mBoard.draw(mBlock); // 繪製目前棋盤和方塊
        std::cout.flush(); // 確保輸出立即顯示

        char inputBuf[1];
        int n = read(STDIN_FILENO, inputBuf, 1);
        // 根據讀取的字元做對應動作
        if (n > 0) {
            
            char ch = inputBuf[0];
            if (ch == 'q') {
                break;
            }
            if (ch == 'a') {
                movePieceLeft();
            }
            if (ch == 'd') {
                movePieceRight();
            }
            if (ch == 's') {
                movePieceDown();
            }
            if (ch == 'w') {
                rotatePiece();
            }
        }

        tick++;
        if (tick == 10) {
            tick = 0;
            movePieceDown();
        }
    }

    if (mGameOver) {
        system("clear");
        mBoard.draw(mBlock);
        std::cout << "game over!" << std::endl;
    }
}