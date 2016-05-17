
#ifndef SIMULATOR_ALGORITHMLOADER_H
#define SIMULATOR_ALGORITHMLOADER_H

#include <vector>
#include "AlgorithmRegistration.h"
#include <iostream>

using namespace std;

class AlgorithmLoader
{
    int counter;
    vector<string> algorithmNames;
    vector<function<unique_ptr<AbstractAlgorithm>()> > algorithmFactories;

    void registerAlgorithm(function<unique_ptr<AbstractAlgorithm>()> algorithmFactory)
    {
        instance.counter++;
        cout << "AAAAAAAAABBBBB" << endl;
        cout << "REGISTERING: " + to_string(instance.counter)  + "A"<< endl;
        instance.algorithmFactories.push_back(algorithmFactory);
    }

    //void setNameForLastAlgorithm(const std::string& algorithmName) {
    //    assert(algorithmFactories.size()-1 == algorithmNames.size());
    //    algorithmNames.push_back(algorithmName);
    //}
public:
    friend class AlgorithmRegistration;

    enum {ALGORITHM_REGISTERED_SUCCESSFULY = 0, FILE_CANNOT_BE_LOADED = -1, NO_ALGORITHM_REGISTERED = -2};

    int loadAlgorithm(const string& path, const string& so_file_name_without_so_suffix);

    vector<unique_ptr<AbstractAlgorithm> > getAlgorithms()const
    {
        vector<unique_ptr<AbstractAlgorithm> > algorithms;
        for(auto algorithmFactoryFunc : algorithmFactories) {
            algorithms.push_back(algorithmFactoryFunc());
        }
        return algorithms;
    }

    const vector<string>& getAlgorithmNames()const { return algorithmNames; }
    size_t size()const { return algorithmFactories.size(); }
    static AlgorithmLoader& getInstance()
    {
        return instance;
    }
private:
    static AlgorithmLoader instance;
};

#endif //SIMULATOR_ALGORITHMLOADER_H
