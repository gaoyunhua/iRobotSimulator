cmake_minimum_required(VERSION 3.5)
project(Simulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        NaiveAlgorithm.cpp
        NaiveAlgorithm.h
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
    Simulator.h FileLister.h)

add_executable(Simulator ${SOURCE_FILES})