
#include "Simulator.h"
#include "FileReader.h"
#include "Cleaner.h"
#include "NaiveAlgorithm.h"

using namespace std;

void Simulator::Simulate(int argc, const char * argv[])
{
    map<string,int> config;
    if (argc >= 2)
    {
        config = FileReader::ReadConfig(argv[1]);
    }
    else
    {
        config = FileReader::ReadConfig("");
    }
    
    if (config["MaxSteps"] == 0)
    {
        cout << "Usage: Config file not found" << endl;
        return;
    }

    House house = FileReader::ReadHouse();

    house.print();
    Point robotLocation = house.findDocking();
    Sensor s(house, robotLocation);
    NaiveAlgorithm n(s);
    AbstractAlgorithm& algorithm = n;

    Cleaner cleaner(algorithm, s, house, robotLocation, config);
    CleanerResult result = cleaner.clean();

    cout << score(result) << endl;

    cout <<
            "Completed:\n# Steps:" + to_string(result.numOfSteps) +
                    "\nPre-Dirt:" + to_string(result.sumDirtInHouse) +
                    "\nPost-Dirt:" + to_string(result.sumDirtInHouse - result.sumDirtCollected) +
                    "\nBack-To-Dock:" + (result.isBackInDocking ? "True" : "False")
                    << endl;
    house.print();
}

int Simulator::score(CleanerResult cleanerResult)
{
    return max(0,
            2000 - ((cleanerResult.sumDirtInHouse - cleanerResult.sumDirtCollected) * 3) +
                    (cleanerResult.isBackInDocking ? 50 : -200));

}
/*
 * 2000
 Minus (position_in_copmetition - 1) * 50
 Plus (winner_num_steps - this_num_steps) * 10
 Minus (sum_dirt_in_house - dirt_collected) * 3
 Plus (is_back_in_docking? 50 : -200)
 *
 */