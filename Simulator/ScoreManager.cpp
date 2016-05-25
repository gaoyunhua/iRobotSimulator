
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
    string separator((unsigned long) (15 + (11 * (numOfHouses + 1))), '-');

    //print first line
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
        cout << separator.c_str() << endl;
    }
}


//    vector<string> results;
//    int prefixLength = (15 + 10 * (housesCount + 1));
//    string prefix(prefixLength, '-');
//    results.push_back(prefix);
//
//    string header = "|             ";
//    for (int i = 0; i < housesCount; i++)
//    {
//        ostringstream ss;
//        ss << setw( 3 ) << setfill( '0' ) << to_string(i+1);
//
//        header += "|" + ss.str() + "      ";
//    }
//    header += "|AVG      |";
//    results.push_back(header);
//
////    map<string, int> a = scoreManager->scores.at("_306543083_G");
//
//    map<string, map<string, int>>::iterator aitr = scoreManager->scores.begin();
//
//    int numOfHouses = (int) aitr->second.size();
//
//    for (int i = 0; i < numOfHouses; i++)
//    {
//        scoreManager->sc
//        string algoScoreString = i == 0 ? "|306543083_G_ " : "|306543083_N_ ";
//        int algoAvg = 0;
//        for (int algoscore : algosScores[i])
//        {
//            algoAvg += algoscore;
//            ostringstream ss;
//            ss << setw( 9 ) << setfill( ' ' ) << to_string(algoscore);
//            algoScoreString += "|" + ss.str();
//        }
//
//        ostringstream ss;
//        string avg = to_string(((float)(algoAvg)) / housesCount);
//        string sortAvg = avg.substr(0, strcspn(avg.c_str(),".") + 3);
//        ss << setw( 9 ) << setfill( ' ' ) << sortAvg;
//        algoScoreString += "|" + ss.str() + "|";
//        results.push_back(algoScoreString);
//    }
//    results.push_back(prefix);
//
//    //TODO: about to finish
//    //TODO: revise scoring function
//    for (auto& result : results)
//        cout << result << endl;
