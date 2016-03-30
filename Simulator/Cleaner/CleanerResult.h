
#ifndef SIMULATOR_CLEANERRESULT_H
#define SIMULATOR_CLEANERRESULT_H

class CleanerResult
{
public:
    int numOfSteps;
    int sumDirtInHouse;
    int sumDirtCollected;
    bool isBackInDocking;

    CleanerResult(int _numOfSteps, int _sumDirtInHouse, int _sumDirtCollected, bool _isBackInDocking) :
            numOfSteps(_numOfSteps), sumDirtInHouse(_sumDirtInHouse), sumDirtCollected(_sumDirtCollected),
            isBackInDocking(_isBackInDocking){}
    CleanerResult(){}
};


#endif //SIMULATOR_CLEANERRESULT_H
