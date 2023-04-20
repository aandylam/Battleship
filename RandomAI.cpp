
#include "RandomAI.h"

namespace BattleShip{
    // Constructor to create a RandomAI class object
    RandomAI::RandomAI(const int &rows, const int &cols, const std::map<char, int> &mapOfShips, const int& aiNumber) : AIPlayer(rows, cols,
                                                                                                         mapOfShips, aiNumber) {}
    //  generates a vector of pairs of all locations on the board
    void RandomAI::getSpaces(const int &rows, const int &cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                randomMoves.emplace_back(std::make_pair(i, j));
            }
        }
    }

    //  generates a random location from the vector of locations and removes the location from vector
    void RandomAI::getMove(int &rowInput, int &colInput, int rows, int cols) {
        int index;
        if (randomMoves.empty()) {
            getSpaces(rows, cols);
        }
        index = getRandomInt(0, randomMoves.size() - 1);
        rowInput = randomMoves.at(index).first;
        colInput = randomMoves.at(index).second;
        randomMoves.erase(randomMoves.begin() + index);
    }

}