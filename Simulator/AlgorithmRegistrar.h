
#ifndef SIMULATOR_ALGORITHMLOADER_H
#define SIMULATOR_ALGORITHMLOADER_H

#include <dlfcn.h>
#include <iostream>
#include <functional>
#include <memory>
#include <list>
#include <vector>
#include <cassert>
#include "AbstractAlgorithm.h"
#include "Debugger.h"

using namespace std;

class AlgorithmRegistrar {
    list<void*> dl_list;
    list<std::string> algorithmNames;
    list<std::function<unique_ptr<AbstractAlgorithm>()>> algorithmFactories;

    void registerAlgorithm(std::function<unique_ptr<AbstractAlgorithm>()> algorithmFactory) {
        PRINT_DEBUG("In Registrar!");
        instance.algorithmFactories.push_back(algorithmFactory);
        PRINT_DEBUG("ADDED!!!");
    }
    void setNameForLastAlgorithm(const std::string& algorithmName) {
//        assert(algorithmFactories.size()-1 == algorithmNames.size());
        algorithmNames.push_back(algorithmName);
    }
public:
    friend class AlgorithmRegistration;
    enum {ALGORITHM_REGISTERED_SUCCESSFULY = 0, FILE_CANNOT_BE_LOADED = -1, NO_ALGORITHM_REGISTERED = -2};
    int loadAlgorithm(const std::string& path, const std::string& so_file_name_without_so_suffix);

    int loadDebugAlgorithm(const string &path, const string &so_file_name_without_so_suffix);

    list<unique_ptr<AbstractAlgorithm>> getAlgorithms()const {
        list<unique_ptr<AbstractAlgorithm>> algorithms;
        for(auto algorithmFactoryFunc : algorithmFactories) {
            algorithms.push_back(algorithmFactoryFunc());
        }
        return algorithms;
    }
    const vector<std::string> getAlgorithmNames()const {
        vector<string> algoNames;
        for(auto algoName : algorithmNames) {
            algoNames.push_back(algoName);
        }
        return algoNames;
    }
    size_t size()const {
        return algorithmFactories.size();
    }
    static AlgorithmRegistrar& getInstance() {
        return instance;
    }
private:
    static AlgorithmRegistrar instance;
};

#endif //SIMULATOR_ALGORITHMLOADER_H
