
#include "AlgorithmRegistrar.h"

//#include "_312908205_A.h"
//#include "_312908205_B.h"
//#include "_312908205_C.h"

using namespace std;

int AlgorithmRegistrar::loadAlgorithm(const string& path, const string& so_file_name_without_so_suffix)
{
    void * dlib;
    size_t size = instance.size();
    PRINT_DEBUG("About to DLOPEN, Registrar size:" + to_string(size));
    PRINT_DEBUG("Opening: " + path + "\nFileName:" + so_file_name_without_so_suffix);
    dlib = dlopen(path.c_str(), RTLD_NOW);
    PRINT_DEBUG("Past DLOPEN");

    if (dlib == NULL)
    {
        PRINT_DEBUG("DLOPEN IS NULL");
        return FILE_CANNOT_BE_LOADED;
    }

    if(instance.size() == size) {
        PRINT_DEBUG("Registrar size:" + to_string(instance.size()) + "Closing handler");
        dlclose(dlib);
        return NO_ALGORITHM_REGISTERED; // no algorithm registered
    }
    PRINT_DEBUG("Registrar size:" + to_string(instance.size()) + " Continuing to set algo name");
    instance.setNameForLastAlgorithm(so_file_name_without_so_suffix);
    PRINT_DEBUG("Algo name set. Storing Handler");
    instance.dlList.push_back(dlib);
    PRINT_DEBUG("Stored Handler");
    return ALGORITHM_REGISTERED_SUCCESSFULY;
}

int AlgorithmRegistrar::loadDebugAlgorithm(const string& path, const string& so_file_name_without_so_suffix)
{
//    std::function<unique_ptr<AbstractAlgorithm>()> a = ([]{return make_unique<_312908205_A>();} );
//    std::function<unique_ptr<AbstractAlgorithm>()> b = ([]{return make_unique<_312908205_B>();} );
//    std::function<unique_ptr<AbstractAlgorithm>()> c = ([]{return make_unique<_312908205_C>();} );
//    instance.algorithmFactories.push_back(a);
//    instance.setNameForLastAlgorithm("312908205_A_");
//    instance.algorithmFactories.push_back(b);
//    instance.setNameForLastAlgorithm("312908205_B_");
//    instance.algorithmFactories.push_back(c);
//    instance.setNameForLastAlgorithm("312908205_C_");
    return ALGORITHM_REGISTERED_SUCCESSFULY;
}

void AlgorithmRegistrar::clear()
{
    algorithmFactories.clear();
    for (auto itr = dlList.begin(); itr != dlList.end(); ++itr)
    {
        dlclose(*itr);
    }
}

AlgorithmRegistrar AlgorithmRegistrar::instance;