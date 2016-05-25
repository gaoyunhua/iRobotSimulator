
#ifndef SIMULATOR_CLEANERRESULT_H
#define SIMULATOR_CLEANERRESULT_H

class CleanerResult
{
public:
    int numOfSteps;
    int sumDirtInHouse;
    int sumDirtCollected;
    bool isBackInDocking;
    bool isDone;
    int position;

    int getActualPosition(int lastWinningPosition)const
    {
        return isDone ? position : lastWinningPosition + 1;
    }
    CleanerResult(int _numOfSteps, int _sumDirtInHouse, int _sumDirtCollected, bool _isBackInDocking, int _position) :
            numOfSteps(_numOfSteps), sumDirtInHouse(_sumDirtInHouse), sumDirtCollected(_sumDirtCollected),
            isBackInDocking(_isBackInDocking), position(_position){}
    CleanerResult(){}
};


#endif //SIMULATOR_CLEANERRESULT_H
