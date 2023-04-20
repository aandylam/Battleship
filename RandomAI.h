
#ifndef BATTLESHIP_RANDOMAI_H
#define BATTLESHIP_RANDOMAI_H

#include "AIPlayer.h"
namespace BattleShip {
    class RandomAI : public AIPlayer {
    public:
        RandomAI(const int&rows, const int&cols, const std:: map <char, int>& mapOfShips, const int& aiNumber);
        virtual ~RandomAI() = default;
        virtual void getSpaces(const int &rows, const int &cols) override;
        virtual void getMove(int &rowInput, int &colInput, int rows, int cols) override;

    protected:
        std::vector<std::pair<int, int>> randomMoves;
    };
}

#endif //BATTLESHIP_RANDOMAI_H
