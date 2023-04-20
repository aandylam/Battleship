
#ifndef BATTLESHIP__GAME_H_
#define BATTLESHIP__GAME_H_
#include <map>
#include <memory>
#include <vector>
#include "Player.h"
#include "Board.h"

namespace BattleShip {
   class Game{
    public:
       Game(const int &rows, const int &cols, const std::map<char, int> &shipMap, const int& seed);
        void playGame();
        // Made these functions static because they are not called on an object
        void pickGame();
        static int pickAI();
        void addPlayers(const int &gameNumber);
        void playRound(Player &player) const;
        void makePlayer(const int &playerNumber);
        void makeAIPlayer(const int &playerNumber, int aiNum);

    private:
        bool game_over() const; // make a private function to check for game over so that both parties don't know the next outcome
        std:: unique_ptr<Player> player1;
        std:: unique_ptr<Player> player2;
        int Rows;
        int Cols;
        std::map<char, int> ShipsMap;
       int Seed;
    };
}

#endif //BATTLESHIP__GAME_H_

