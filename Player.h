
#ifndef BATTLESHIP__PLAYER_H_
#define BATTLESHIP__PLAYER_H_

#include <string>
#include <map>
#include "Board.h"

namespace BattleShip {

    using Ships = std::map<char, int>;

    class Player {
    public:
        Player(const int&rows, const int&cols, const std:: map <char, int>& mapOfShips);  //  allows for compiler automatic initialization for at
        virtual ~Player() = default;
        const std::string &getName() const;
        const Ships &getShipsMap() const;
        void updateShipsMap(const char &shipName);  //  decrements the ship's health
        Board& getFiringBoard();
        Board& getPlacementBoard();
        virtual void place_ships(Board& board, const int &rows, const int &cols) = 0;
        virtual void getMove(int &rowInput, int &colInput, int rows, int cols) = 0;
        void fire(const char &shipName, const int &rowInput, const int &colInput);
        void set_opponent(Player& other_player);
        Player* get_opponent() const;

    protected:
        std::string Name;
        Ships ShipsMap;  //  each player gets a map of ships
        Board firing_board;
        Board placement_board;
        Player* opponent;

    };
}

#endif //BATTLESHIP__PLAYER_H_
