
#include "Simulator.h"
#include "FileReader.h"
#include "House.h"
#include "Cleaner.h"
#include "NaiveAlgorithm.h"

using namespace std;

void Simulator::Simulate(int argc, const char * argv[])
{
    if (argc < 2)
    {
        cout << "Usage: config.ini missing" << endl;
    }

    //Read Config file:
    map<string,int> config = FileReader::ReadConfig("");

    //Read House

    enum {rows = 19, cols = 80};
    char houseStructure[rows][cols + 1] = {
        //             1         2         3         4         5         6         7
        //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
            "W  99   D              1234321                                                 W", // 1
            "W  99      WWWWWWW     1234321                     W                       1   W", // 2
            "W              W                                   W   555                 2   W", // 3
            "W              W                                   W   555                 3   W", // 4
            "W              W           WWWWWWWWWWWWWWWWWWWWWWWWW                       4   W", // 5
            "W              W                                                           5   W", // 6
            "W              W                                                           6   W", // 7
            "W                          WWWWWWWWWWWWWWWWWWWWWW  WWWWWWW                 7   W", // 8
            "W         1         2         3         4         5W 999 W  6         7        W", // 9
            "W              W           444                     W 999 W                 9   W", // 10
            "W              W           444                     W 999 W                 8   W", // 11
            "W              W                                   W     W                 7   W", // 12
            "W              W                                   WW   WW                 6   W", // 13
            "W              W                                    W   W                  5   W", // 14
            "W              W                                                           4   W", // 15
            "W              W                                                           3   W", // 16
            "W              W                                                               W", // 17
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
    };

    char** housy = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        housy[i] = new char[cols];
        for (int j = 0; j < cols; j++)
            housy[i][j] = houseStructure[i][j];
    }

    House house = House(19, 81, housy);
    Point robotLocation = house.findDocking();
    Sensor s(house, robotLocation);
    NaiveAlgorithm n(s);
    AbstractAlgorithm& algorithm = n;

//    AbstractSensor& sensor = s;

    Cleaner cleaner(algorithm, s, house, FileReader::ReadConfig(""));

    CleanerResult result = cleaner.clean();


//Winner Formula: positionInCompetition, winnerNumSteps, thisNumSteps, sumDirtInHouse, dirtCollected, isBackInDocking

}


