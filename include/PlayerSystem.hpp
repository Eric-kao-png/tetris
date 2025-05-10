#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <sstream>
#include <iomanip>

#define YES_COMMEND "y"

class PlayerSystem {
    private:

    std::vector< std::pair<std::string, int> > players;

    void loadData ();
    void writeFile ();

    public:

    PlayerSystem ();

    void showPlayersRank ();
    void inputPlayer (int score);
};

#endif // PLAYER_SYSTEM_H