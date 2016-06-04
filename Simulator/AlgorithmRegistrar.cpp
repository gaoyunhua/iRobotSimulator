
#include "AlgorithmRegistrar.h"
#include "_306543083_G.h"
#include "_306543083_N.h"

using namespace std;

int AlgorithmRegistrar::loadAlgorithm(const string& path, const string& so_file_name_without_so_suffix)
{
    void * dlib;
    size_t size = instance.size();
    PRINT_DEBUG("About to DLOPEN, Registrar size:" + to_string(size));
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
    instance.dl_list.push_back(dlib);
    PRINT_DEBUG("Stored Handler");
    return ALGORITHM_REGISTERED_SUCCESSFULY;
}

int AlgorithmRegistrar::loadDebugAlgorithm(const string& path, const string& so_file_name_without_so_suffix)
{
    std::function<unique_ptr<AbstractAlgorithm>()> a = ([]{return make_unique<_306543083_G>();} );
    std::function<unique_ptr<AbstractAlgorithm>()> b = ([]{return make_unique<_306543083_N>();} );
    instance.algorithmFactories.push_back(a);
    instance.setNameForLastAlgorithm("306543083_G_");
    instance.algorithmFactories.push_back(b);
    instance.setNameForLastAlgorithm("306543083_N_");

//    instance.setNameForLastAlgorithm(so_file_name_without_so_suffix);
    return ALGORITHM_REGISTERED_SUCCESSFULY;
}

AlgorithmRegistrar AlgorithmRegistrar::instance;