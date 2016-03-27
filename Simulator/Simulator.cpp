
#include "Simulator.h"
#include "FileReader.h"
#include "House.h"
#include <iostream>
#include <map>

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
//    House house = House();





}
