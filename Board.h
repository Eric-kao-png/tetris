#ifndef BOARD_H
#define BOARD_H

#include "Block.h"
#include <iostream>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

class Board {
    private:

    int mGrid [BOARD_HEIGHT][BOARD_WIDTH];

    public:

    Board ();

    bool isCellEmpty (int pX, int pY);
    bool isCollision (int pType, int pRotation, int pX, int pY); // 檢查方塊在給定位置/旋轉是否發生碰撞
    void placeBlock (const Block& pBlock); // 將方塊固定到棋盤上
    int checkLines (); // 檢查已滿的行並計算清除了多少行
    void clearLine (int pY); // 消除已滿的行
    bool isGameOver (); // 判斷最頂端是否有方塊（遊戲是否結束）
    void draw (const Block& currentBlock); // 繪製棋盤（包含當前方塊）
};

#endif