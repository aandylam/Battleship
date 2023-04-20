
#ifndef BATTLESHIP_CHEATINGAI_H
#define BATTLESHIP_CHEATINGAI_H
#include "AIPlayer.h"
#include <vector>
namespace BattleShip {
    class CheatingAI : public AIPlayer {
    public:
        CheatingAI(const int&rows, const int&cols, const std:: map <char, int>& mapOfShips, const int& aiNumber);
        virtual ~CheatingAI() = default;
        virtual void getSpaces(const int &rows, const int &cols) override;
        virtual void getMove(int &rowInput, int &colInput, int rows, int cols) override;
    protected:
        std::vector<std::pair<int,int>> moves;
    };

}



#endif //BATTLESHIP_CHEATINGAI_H
