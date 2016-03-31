
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
    Point robotLocation = house.findDocking();
    Sensor s(house, robotLocation);
    NaiveAlgorithm n(s);
    AbstractAlgorithm& algorithm = n;

    Cleaner cleaner(algorithm, s, house, robotLocation, config);
    CleanerResult result = cleaner.clean();

    cout << score(result) << endl;

    config.clear();
}

int Simulator::score(CleanerResult cleanerResult)
{
    return max(0,
            2000 - ((cleanerResult.sumDirtInHouse - cleanerResult.sumDirtCollected) * 3) +
                    (cleanerResult.isBackInDocking ? 50 : -200));

}