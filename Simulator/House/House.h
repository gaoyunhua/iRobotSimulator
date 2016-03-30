
#ifndef SIMULATOR_HOUSE_H
#define SIMULATOR_HOUSE_H

#import <iostream>
#include "Point.h"

using namespace std;

class House
{


    char** house;
    int rows;
    int columns;
    Point docking = Point(-1, -1);
    Point robot = Point(-1, -1);

public:
    House(int houseRows, int houseColumns, char** _house);
    House(int rows, int columns);
    House(const House& aHouse);
    ~House();

    char point(Point point);
    void setPoint(Point point, char value);

    bool isWall(Point point);
    int dirtLevel(Point point);
    int cleanOneUnit(Point point);
    Point findDocking();
    int amountOfDirt();

    enum ItemType {DOCKING = 'D', WALL = 'W', ROBOT = 'R'};
    Point find(ItemType itemType);

};

//class House {
//    enum {rows = 19, cols = 80}; // this is an example for an hard coded house...
//    char house[rows][cols + 1] = {
//            //             1         2         3         4         5         6         7
//            //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
//            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
//            "W  99   D              1234321                                                 W", // 1
//            "W  99      WWWWWWW     1234321                     W                       1   W", // 2
//            "W              W                                   W   555                 2   W", // 3
//            "W              W                                   W   555                 3   W", // 4
//            "W              W           WWWWWWWWWWWWWWWWWWWWWWWWW                       4   W", // 5
//            "W              W                                                           5   W", // 6
//            "W              W                                                           6   W", // 7
//            "W                          WWWWWWWWWWWWWWWWWWWWWW  WWWWWWW                 7   W", // 8
//            "W         1         2         3         4         5W 999 W  6         7        W", // 9
//            "W              W           444                     W 999 W                 9   W", // 10
//            "W              W           444                     W 999 W                 8   W", // 11
//            "W              W                                   W     W                 7   W", // 12
//            "W              W                                   WW   WW                 6   W", // 13
//            "W              W                                    W   W                  5   W", // 14
//            "W              W                                                           4   W", // 15
//            "W              W                                                           3   W", // 16
//            "W              W                                                               W", // 17
//            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
//    };
//    Point docking;
//    Point findDocking() {
//        for(size_t row = 0; row < rows; ++row) {
//            for(size_t col = 0; col < cols; ++col) {
//                if(house[row][col] == House::DOCKING) {
//                    return Point(col, row); // col == X, row == Y
//                }
//            }
//        }
//        return Point(-1, -1); // we didn't find docking...
//    }
//public:
//    enum {DOCKING = 'D', WALL = 'W'};
//    House(): docking(findDocking()) {}
//    void print()const {
//        cout << endl;
//        cout << "          1         2         3         4         5         6         7         " << endl;
//        cout << "01234567890123456789012345678901234567890123456789012345678901234567890123456789" << endl;
//        for(size_t row = 0; row < rows; ++row) {
//            cout << house[row] << " " << row << endl;
//        }
//        cout << endl << "docking station at: " << docking.getX() << ", " << docking.getY() << endl;
//    }
//};


#endif //SIMULATOR_HOUSE_H
