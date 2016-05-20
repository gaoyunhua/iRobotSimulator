
#ifndef SIMULATOR_SCOREMANAGER_H
#define SIMULATOR_SCOREMANAGER_H

#include <list>
#include <map>
#include <string>

using namespace std;

class ScoreManager
{

public:
    map<string, map<string, int>> scores;
	ScoreManager(){ scores.clear(); }
	void addScore(const string& algoName, const string& houseName, int score);
    void printScoreTable();
};



#endif //SIMULATOR_SCOREMANAGER_H
