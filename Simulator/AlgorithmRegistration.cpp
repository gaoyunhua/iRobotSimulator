#include "AlgorithmRegistrar.h"
#include "AlgorithmRegistration.h"
#include "my_make_unique.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<unique_ptr<AbstractAlgorithm>()> algorithmFactory) {
    AlgorithmRegistrar::getInstance().registerAlgorithm(algorithmFactory);
}