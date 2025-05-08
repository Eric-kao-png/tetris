#ifndef BOARD_H
#define BOARD_H

#include "Block.h"
#include <iostream>

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 21

enum {EMPTY_POS, FULL_POS};

class Board {
    private:

    int mGrid [BOARD_HEIGHT][BOARD_WIDTH];

    bool isPosEmpty (int pX, int pY);
    void clearLine (int pY); // 消除已滿的行

    public:

    Board ();

    bool isCollision (int pType, int pRotation, int pX, int pY); // 檢查方塊在給定位置/旋轉是否發生碰撞
    void placeBlock (const Block& pBlock); // 將方塊固定到棋盤上
    int clearLines (); // 檢查已滿的行並計算清除了多少行
    bool isGameOver (); // 判斷最頂端是否有方塊（遊戲是否結束）
    void draw (const Block& currentBlock, int score); // 繪製棋盤（包含當前方塊）
};

#endif // BOARD_H