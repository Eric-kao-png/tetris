#include "../include/Game.hpp"
#include "../include/PlayerSystem.hpp"
#include <termios.h>
#include <unistd.h>

namespace {
    void useNewTermios (struct termios& oldt, struct termios& newt) {
        tcgetattr (STDIN_FILENO, &oldt); 
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr (STDIN_FILENO, TCSANOW, &newt); 
    }

    void useOldTermios (struct termios& oldt) {
        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
    }

    void askSaving (Game& game, PlayerSystem& ps) {
        std::string opt;
        std::cout << "do you want to save the record? Enter \"";
        std::cout << YES_COMMEND;
        std::cout << "\" for YES: ";
        std::cin >> opt;
        if (opt == YES_COMMEND) {
            ps.inputPlayer (game.getScore());
        }
    }

    void askShowingRank (PlayerSystem& ps) {
        std::string opt;
        std::cout << "do you want to see the rank? Enter \"";
        std::cout << YES_COMMEND;
        std::cout << "\" if YES: ";
        std::cin >> opt;
        if (opt == YES_COMMEND) {
            ps.showPlayersRank();
        }
    }

    bool askPlayingAgain () {
        std::string opt;
        std::cout << "do you want to play again? Enter \"";
        std::cout << YES_COMMEND;
        std::cout << "\" if YES: ";
        std::cin >> opt;
        if (opt == YES_COMMEND) {
            return true;
        }
        return false;
    }
}

int main (void) {
    
    bool playAgain = false;
    do {
        struct termios oldt, newt;
        useNewTermios (oldt, newt);

        Game game;
        PlayerSystem ps;
        game.run();

        useOldTermios (oldt);

        askSaving (game, ps);
        askShowingRank (ps);
        playAgain = askPlayingAgain();
        
    } while (playAgain);

    return 0;
}