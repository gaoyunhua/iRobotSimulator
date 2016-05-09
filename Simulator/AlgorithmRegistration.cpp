
#include <memory>
#include "AbstractAlgorithm.h"
#include "AlgorithmRegistration.h"

AlgorithmRegistration::AlgorithmRegistration(std::function < std::unique_ptr<AbstractAlgorithm>() > )
{

}

