#include "../include/PlayerSystem.hpp"

#define PLAYERS_PATH "../data/players.txt"

namespace {
    bool playerComp (std::pair<std::string, int>& p1, std::pair<std::string, int>& p2) {
        return (p1.second >= p2.second);
    }
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
        while (getline (inputFile, line)) {
            std::istringstream iss(line);
            std::string name;
            int score;
            getline (iss, name, ',');
            iss >> score;
            
            players.emplace_back (name, score);
        }

        inputFile.close();

    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void PlayerSystem::inputPlayer (int score) {
    std::string name = inputMessage();

    players.emplace_back (name, score);
    std::sort (players.begin(), players.end(), playerComp);

    writeFile ();
}

std::string PlayerSystem::inputMessage () const {
    std::string name;
    std::cout << "Please enter your name: ";
    std::cin >> name;
    std::cout << std::endl;
    return name;
}

void PlayerSystem::writeFile () const {
    std::ofstream outputFile (PLAYERS_PATH);

    try {
        if (!outputFile) {
            throw std::runtime_error("output failed!\n");
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

void PlayerSystem::showPlayersRank () const {
    std::cout << "======Rank======" << std::endl;

    size_t playersSize = players.size();
    std::cout << "Rank Players             Score" << std::endl; 
    for (size_t i  = 0; i < playersSize; i++) {
        std::cout 
        << std::left << std::setw(5) << i + 1 
        << std::setw(20) << players.at(i).first 
        << std::setw(6) << players.at(i).second 
        << std::endl;
    }

    std::cout << "================" << std::endl;
}