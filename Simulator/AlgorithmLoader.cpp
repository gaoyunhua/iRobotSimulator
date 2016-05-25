
#include <dlfcn.h>
#include <algorithm>
#include <iostream>
#include "AlgorithmLoader.h"

using namespace std;



int AlgorithmLoader::loadAlgorithm(const string& path, const string& so_file_name_without_so_suffix)
{
    void *handler = dlopen(path.c_str(), RTLD_NOW);
    if (handler == nullptr)
    {
        cout << "DEBUG: dlopen error: " << dlerror() << endl;
        return FILE_CANNOT_BE_LOADED;
    }

//    typedef AlgorithmRegistration* (*algo_t)();
//
//    string dldl = "register_me_" + so_file_name_without_so_suffix;
//
//    void* regptr = dlsym(handler, dldl.c_str());
//
//    algo_t getreg = reinterpret_cast<algo_t>(reinterpret_cast<long>(regptr));
//    if (getreg == nullptr)
//    {
//        cout << "DEBUG: dlsym error: " << dlerror() << endl;
//        dlclose(handler);
//        return NO_ALGORITHM_REGISTERED;
//    }
//
////    getreg();
////    AlgorithmRegistration* reg = getreg();// pushes the factory function into algoFactories

//    dlclose(handler);

    return ALGORITHM_REGISTERED_SUCCESSFULY;
}

AlgorithmLoader AlgorithmLoader::instance;