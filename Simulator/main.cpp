//
//  main.cpp
//  Simulator
//
//  Created by Roni Poyas on 26/03/2016.
//  Copyright (c) 2016 Roni Poyas. All rights reserved.
//

#include <iostream>
#include "Simulator.h"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Simulator simulator;
    simulator.Simulate(argc, argv);
    return 0;
}