
#include "ScoreManager.h"
#include "Debugger.h"
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <cstring>
#include <iomanip>

using namespace std;

void ScoreManager::addScore(const string& algoName, const string& houseName, int score)
{
    scores[algoName][houseName] = score;

    PRINT_DEBUG("score manager added entry for algorithm: " << algoName.c_str() << '\n'
                << "with house: " << houseName.c_str() << '\n'
                << "score: " << scores[algoName][houseName] << '\n');
}

void ScoreManager::printScoreTable()
{
    map<string, map<string, int>>::iterator aitr = scores.begin();
    int numOfHouses = (int) aitr->second.size();
    string separator((unsigned long) (15 + (11 * (numOfHouses + 1))), '-');

    cout << separator.c_str() << endl;
    cout << "|             |";
    map<string, int>::iterator hitr;
    for (hitr = aitr->second.begin(); hitr != aitr->second.end(); ++hitr) {
        int len = (int) ((9 < hitr->first.size()) ? 9 : hitr->first.size());
        string hName = hitr->first.substr(0, len);
        cout << hName << string(10 - len, ' ') << '|';
    }
    cout << "AVG       |" << endl;
    cout << separator.c_str() << endl;

    for (aitr = scores.begin(); aitr != scores.end(); ++aitr) {
        cout << '|' << aitr->first.c_str() << " |";
        int sum = 0;
        for (hitr = aitr->second.begin(); hitr != aitr->second.end(); ++hitr) {
            int score = hitr->second;
            cout << setw(10) << score << '|';
            sum += score;
        }
        float avg = sum / ((float) numOfHouses);
        cout << fixed;
        cout.precision(2);
        cout << setw(10) << avg << '|' << endl;
        cout << separator.c_str() << endl;
    }
}
