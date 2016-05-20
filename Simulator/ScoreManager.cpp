
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

void ScoreManager::printScoreTable() {
    //int numOfAlgos = scores.size();
    map<string, map<string, int>>::iterator aitr = scores.begin();

    int numOfHouses = (int) aitr->second.size();
    string lineSeperator(15 + (11 * (numOfHouses + 1)), '-');

    //print first line
    cout << lineSeperator.c_str() << endl;
    cout << "|             |";
    map<string, int>::iterator hitr;
    for (hitr = aitr->second.begin(); hitr != aitr->second.end(); ++hitr) {
        int len = (9 < hitr->first.size()) ? 9 : hitr->first.size();
        string hName = hitr->first.substr(0, len);
        cout << hName << string(10 - len, ' ') << '|';
    }
    cout << "AVG       |" << endl;
    cout << lineSeperator.c_str() << endl;

    //loop over algorithms
    for (aitr = scores.begin(); aitr != scores.end(); ++aitr) {
        //print algorithm name
        cout << '|' << aitr->first.c_str() << " |";
        //go over houses
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
        cout << lineSeperator.c_str() << endl;
    }
}

