
#include "CheatingAI.h"

namespace BattleShip{
// Constructor for creating a CheatingAI class object
    CheatingAI::CheatingAI(const int &rows, const int &cols, const std::map<char, int> &mapOfShips, const int& aiNumber) : AIPlayer(rows, cols,
                                                                                                                                    mapOfShips, aiNumber) {}
    //  gets all the positions of the ships
    void BattleShip::CheatingAI::getSpaces(const int &rows, const int &cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (opponent->getPlacementBoard().getChar(i, j) != '*') {
                    moves.emplace_back(std::make_pair(i, j));
                }
            }
        }
    }

    //  gets the next closest ship's postition and removes it from vector
    void CheatingAI::getMove(int &rowInput, int &colInput, int rows, int cols) {
        getSpaces(rows, cols);
        rowInput = moves.at(0).first;
        colInput = moves.at(0).second;
        moves.erase(moves.begin());
        rows++; cols++;
    }

}

