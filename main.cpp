#include "Game.h"
#include <termios.h>

int main (void) {
    struct termios oldt, newt;
    tcgetattr (STDIN_FILENO, &oldt); // 取得當前終端設定
    newt = oldt;
    newt.c_cflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 1;
    tcsetattr (STDIN_FILENO, TCSANOW, &newt); // 套用設定

    system("clear");
    Game game;
    game.loop();

    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}