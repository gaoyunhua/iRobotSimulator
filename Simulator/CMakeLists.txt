cmake_minimum_required(VERSION 3.5)
project(Simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

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
    Simulator.h FileLister.h AlgorithmLoader.cpp AlgorithmLoader.h _306543083_N.cpp _306543083_N.h _306543083_G.cpp _306543083_G.h score_formula.cpp Debugger.h AlgorithmRegistration.h AlgorithmRegistration.cpp ScoreManager.cpp ScoreManager.h)

set(G_FILES _306543083_G.cpp _306543083_G.h AlgorithmRegistration.h AlgorithmRegistration.cpp Direction.h AbstractAlgorithm.h SensorInformation.h AlgorithmLoader.cpp AlgorithmLoader.h)
set(N_FILES _306543083_N.cpp _306543083_N.h AlgorithmRegistration.h AlgorithmRegistration.cpp Direction.h AbstractAlgorithm.h SensorInformation.h AlgorithmLoader.cpp AlgorithmLoader.h)

add_executable(Simulator ${SOURCE_FILES})

#add_library(_306543083_G.so SHARED ${G_FILES})
#add_library(_306543083_N.so SHARED ${N_FILES})

add_library(score_formula.so SHARED score_formula.cpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#include_directories(_306543083_G.so PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(_306543083_N.so PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#TARGET_LINK_LIBRARIES(Simulator _306543083_G.so _306543083_N.so)
