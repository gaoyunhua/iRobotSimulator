cmake_minimum_required(VERSION 3.5)
project(Simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Cleaner.cpp
        Cleaner.h
        CleanerResult.cpp
        CleanerResult.h
        FileReader.cpp
        FileReader.h
        House.cpp
        House.h
        Point.cpp
        Point.h
        AbstractAlgorithm.h
        AbstractSensor.h
        Direction.h
        SensorInformation.h
        Sensor.cpp
        Sensor.h
        main.cpp
        Simulator.cpp
        Simulator.h
        FileLister.h
        AlgorithmRegistrar.cpp AlgorithmRegistrar.h
        score_formula.cpp
        Debugger.h
        AlgorithmRegistration.h AlgorithmRegistration.cpp
        ScoreManager.cpp ScoreManager.h my_make_unique.h
        _306543083_A.h _306543083_A.cpp _306543083_B.h _306543083_B.cpp _306543083_C.h _306543083_C.cpp
        GeneralAlgorithm.h GeneralAlgorithm.cpp Location.cpp Location.h Battery.h Common.h Common.cpp HouseMap2.cpp HouseMap2.h
        Encoder.h Encoder.cpp Montage.cpp Montage.h)

#AbstractAlgorithm.h is part of BOTH

#AlgorithmRegistrar.h is part of the simulation
#AlgorithmRegistrar.cpp is part of the simulation

#AlgorithmRegistration.h is part of BOTH
#AlgorithmRegistration.cpp is part of the simulation

#set(ALGO_FILES my_make_unique.h AbstractAlgorithm.h AlgorithmRegistration.h)


#add_library(algo.o STATIC ${ALGO_FILES})

#set(N_FILES _306543083_N.cpp)

add_executable(Simulator ${SOURCE_FILES})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_library(_306543083_G.so SHARED ${G_FILES})
#add_library(_306543083_N.so SHARED ${N_FILES})

#target_link_libraries(_306543083_G.so algo.o)
#target_link_libraries(_306543083_N.so algo.o)


#install(TARGETS _306543083_G.so DESTINATION /Users/Roni/Desktop/working/)
#install(TARGETS _306543083_G.so _306543083_N.so DESTINATION /Users/Roni/Desktop/working/)


#install(TARGETS  DESTINATION /Users/Roni/Desktop/working/)

#
#add_library(score_formula.so SHARED score_formula.cpp)
#

#

#TARGET_LINK_LIBRARIES(Simulator _306543083_G.so _306543083_N.so)
