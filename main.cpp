#include "Game.h"
#include "PlayerSystem.hpp"
#include <termios.h>
#include <unistd.h>

int main (void) {
    struct termios oldt, newt;
    tcgetattr (STDIN_FILENO, &oldt); // 取得當前終端設定
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newt); // 套用設定

    system("clear");
    Game game;
    PlayerSystem ps;
    game.run();

    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);

    std::string opt_1;
    std::cout << "do you want to save the record? Enter \""  YES_COMMEND  "\" for YES: ";
    std::cin >> opt_1;
    if (opt_1 == YES_COMMEND) {
        ps.inputPlayer (game.getScore());
    }

    std::string opt_2;
    std::cout << "do you want to see the rank? Enter \"" YES_COMMEND "\" if YES: ";
    std::cin >> opt_2;
    if (opt_2 == YES_COMMEND) {
        ps.showPlayersRank();
    }

    return 0;
}