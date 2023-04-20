

#ifndef BATTLESHIP__READFILE_H_
#define BATTLESHIP__READFILE_H_
#include <map>
namespace BattleShip {
    void extractInfo(std::istream &file, int &rows, int &columns, std::map<char, int> &shipInfo);
}
#endif //BATTLESHIP__READFILE_H_
