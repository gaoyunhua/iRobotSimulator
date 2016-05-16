
#include <memory>
#include <iostream>
#include <map>
#include "AbstractAlgorithm.h"
#include "AlgorithmRegistration.h"
#include "AlgorithmLoader.h"

AlgorithmRegistration::AlgorithmRegistration(std::function < std::unique_ptr<AbstractAlgorithm>() > func)
{
    AlgorithmLoader::getInstance().registerAlgorithm(func);
}

