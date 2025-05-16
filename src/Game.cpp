#include "../include/Game.hpp"

Game::Game () : mGameOver(false), mPiece(Piece(0)), mScore(0) {
    srand (static_cast<unsigned int> (std::time (nullptr)));
    spawnNewBlock ();
}

void Game::spawnNewBlock () {
    int newType = rand() % PIECE_TYPE;
    mPiece.setType(newType);
    mPiece.setRotation(0);
    mPiece.setX(BOARD_WIDTH / 2 - PIECE_SIZE / 2);
    mPiece.setY(0);

    if (mBoard.isCollision (mPiece.getType(), mPiece.getRotation(), mPiece.getX(), mPiece.getY())) {
        mGameOver = true;
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

bool Game::checkCollision () {
    if (mBoard.isCollision (mPiece.getType(), mPiece.getRotation(), mPiece.getX(), mPiece.getY() + 1) == true) {
        mBoard.placePiece (mPiece);
        int clearedLines = mBoard.checkLines();
        mScore += calculateScore (clearedLines);
        spawnNewBlock();
        return true;
    }
    return false;
}

void Game::clearAndDraw () {
    system("clear");
    mBoard.draw(mPiece, mScore);
}

char Game::receiveInput () {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval tv = {1, 0};
    int retval = select (STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

    if (retval > 0 && FD_ISSET (STDIN_FILENO, &readfds)) {
        char input = 0;
        if (read (STDIN_FILENO, &input, 1) > 0) {
            return input;
        }
    }

    return 0;
}

void Game::processInput (char input) {
    switch (input) {
        case 'q':
            mGameOver = true; break;
        case 'a':
            mPiece.movePieceLeft(mBoard); break;
        case 'd':
            mPiece.movePieceRight(mBoard); break;
        case 'w':
            mPiece.rotatePiece(mBoard); break;
        case 's':
            mPiece.movePieceDown(mBoard);
            checkCollision();
            break;
        default:
            return;
    }
}

void Game::run () {
    auto lastDrop = std::chrono::steady_clock::now();

    while (!mGameOver) {
        clearAndDraw();

        char input = receiveInput();
        processInput (input);
            
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds> (now - lastDrop) >= std::chrono::seconds(1)) {
            if (checkCollision() == false) {
                mPiece.movePieceDown(mBoard);
            }
            lastDrop = now;
        }

        if (mBoard.isGameOver() == true) {
            mGameOver = true;
        }
    }

    if (mGameOver) {
        clearAndDraw();
        std::cout << "game over!" << std::endl;
    }
}
