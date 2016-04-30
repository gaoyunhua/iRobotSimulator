
#include "Simulator.h"
#include "FileReader.h"
#include "Cleaner.h"
#include "NaiveAlgorithm.h"

static const int NumberOfConfigParams = 5;
static const string UsageMessage = "Usage: simulator [-config <config path>] [-house_path <house path>] [-algorithm_path <algorithm path>]";

void Simulator::Simulate(int argc, const char * argv[])
{
    map<string,int> config;

    string configParamPath = ParseConfig(argc, argv);
    config = FileReader::ReadConfig(configParamPath);

    if (config.size() != NumberOfConfigParams)
    {
        cout << UsageMessage << endl;
        return;
    }


    House house = FileReader::ReadHouse();
    Point robotLocation = house.findDocking();
    Sensor s(house, robotLocation);
    NaiveAlgorithm n(s);
    AbstractAlgorithm& algorithm = n;

    Cleaner cleaner(algorithm, s, house, robotLocation, config);
    CleanerResult result = cleaner.clean();

    cout << Score(result) << endl;

    config.clear();
}

string Simulator::ParseConfig(int argc, const char* argv[])
{
    string ConfigParamPrefix = "-config";
    return ParseParam(ConfigParamPrefix, argc, argv);
}

string Simulator::ParseParam(string paramPrefix, int argc, const char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        string param = argv[i];
        if (param.compare(paramPrefix) == 0)
        {
            if ((i+1) <= argc)
            {
                return argv[i+1];
            }
        }
    }
    return "";
}

int Simulator::Score(CleanerResult cleanerResult)
{
    return max(0,
            2000 - ((cleanerResult.sumDirtInHouse - cleanerResult.sumDirtCollected) * 3) +
                    (cleanerResult.isBackInDocking ? 50 : -200));

}