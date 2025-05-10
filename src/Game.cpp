#include "../include/Game.hpp"

Game::Game () : mGameOver(false), mBlock(Block(0)), mScore(0) {
    srand (static_cast<unsigned int> (std::time (nullptr)));
    spawnNewBlock ();
}

void Game::spawnNewBlock () {
    int newType = rand() % 7;
    mBlock.mType = newType;
    mBlock.mRotation = 0;
    mBlock.mX = BOARD_WIDTH / 2 - PIECE_SIZE / 2;
    mBlock.mY = 0;

    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY)) {
        mGameOver = true;
    }
}

void Game::movePieceDown () {
    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY + 1) == false) {
        mBlock.mY += 1;
    }
}

void Game::movePieceLeft () {
    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX - 1, mBlock.mY) == false) {
        mBlock.mX -= 1;
    }
}

void Game::movePieceRight () {
    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX + 1, mBlock.mY) == false) {
        mBlock.mX += 1;
    }
}

void Game::rotatePiece () {
    if (mBoard.isCollision (mBlock.mType, (mBlock.mRotation + 1) % 4, mBlock.mX, mBlock.mY) == false) {
        mBlock.mRotation = (mBlock.mRotation + 1) % 4;
    }
}

int Game::calculateScore (int clearedLines) {
    if (clearedLines == 1) {
        return ONE_LINE_SCORE;
    }
    if (clearedLines == 2) {
        return TWO_LINE_SCORE;
    }
    if (clearedLines == 3) {
        return THREE_LINE_SCORE;
    }
    if (clearedLines == 4) {
        return FOUR_LINE_SCORE;
    }

    return 0;
}

void Game::run () {
    auto lastDrop = std::chrono::steady_clock::now();

    while (!mGameOver) {
        system("clear");
        mBoard.draw(mBlock, mScore); // 繪製目前棋盤和方塊

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval tv = {1, 0};
        int retval = select (STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

        if (retval > 0 && FD_ISSET (STDIN_FILENO, &readfds)) {
            char input = 0;
            if (read (STDIN_FILENO, &input, 1) > 0) {
                switch (input) {
                    case 'q':
                    mGameOver = true; break;
                    case 'a':
                    movePieceLeft(); break;
                    case 'd':
                    movePieceRight(); break;
                    case 'w':
                    rotatePiece(); break;
                    case 's':
                    movePieceDown();

                    if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY + 1) == true) {

                        mBoard.placeBlock (mBlock);
                        int clearedLines = mBoard.clearLines();
                        mScore += calculateScore (clearedLines);
                        spawnNewBlock();
        
                    } break;
                }
            }
        }

        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastDrop) >= std::chrono::seconds(1)) {

            if (mBoard.isCollision (mBlock.mType, mBlock.mRotation, mBlock.mX, mBlock.mY + 1) == true) {

                mBoard.placeBlock (mBlock);
                int clearedLines = mBoard.clearLines();
                mScore += calculateScore (clearedLines);
                spawnNewBlock();

            } else {

                movePieceDown();
                
            }

            lastDrop = now;
        }

        if (mBoard.isGameOver() == true) {
            mGameOver = true;
        }
    }

    if (mGameOver) {
        system("clear");
        mBoard.draw(mBlock, mScore);
        std::cout << "game over!" << std::endl;
    }
}

int Game::getScore () {
    return mScore;
}