#include "../include/PlayerSystem.hpp"

#define PLAYERS_PATH "../data/players.txt"

bool playerComp (std::pair< std::string, int >& p1, std::pair< std::string, int >& p2) {
    return (p1.second >= p2.second);
}

PlayerSystem::PlayerSystem () {
    loadData ();
}

void PlayerSystem::loadData () {
    try {
        std::ifstream inputFile(PLAYERS_PATH);

        if (!inputFile) {
            throw std::runtime_error("\"Players.txt\" does not exist!\n");
        }

        std::string line;
        while ( getline (inputFile, line) ) {
            std::string name, scoreStr;
            int score;
            std::istringstream iss(line);
            getline (iss, name, ',');
            iss >> score;
            
            players.push_back (std::pair<std::string, int> (name, score));
        }

        inputFile.close();

    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void PlayerSystem::inputPlayer (int score) {
    std::string name;
    std::cout << "Please enter your name: ";
    std::cin >> name;
    std::cout << std::endl;

    players.push_back (std::pair< std::string, int > (name, score));

    std::sort (players.begin(), players.end(), playerComp);

    writeFile ();
}

void PlayerSystem::writeFile () {
    std::ofstream outputFile(PLAYERS_PATH);

    try {
        if (!outputFile) {
            throw std::runtime_error("\"Players.txt\" does not exist!");
        }

        size_t playersSize = players.size();
        for (size_t i = 0; i < playersSize; i++) {
            outputFile << players.at(i).first << "," << players.at(i).second << std::endl;
        }
        
        outputFile.close();

    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void PlayerSystem::showPlayersRank () {
    std::cout << "======Rank======" << std::endl;

    size_t playersSize = players.size();
    std::cout << "Rank Players             Score" << std::endl; 
    for (size_t i  = 0; i < playersSize; i++) {
        std::cout << std::left << std::setw(5) << i + 1 << std::setw(20) << players.at(i).first << std::setw(6) << players.at(i).second << std::endl;
    }

    std::cout << "================" << std::endl;
}