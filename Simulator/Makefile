.DEFAULT_GOAL := all

# place here your source files
src = Cleaner.cpp CleanerResult.cpp FileReader.cpp House.cpp Point.cpp Sensor.cpp main.cpp Simulator.cpp ScoreManager.cpp score_formula.cpp AlgorithmRegistrar.cpp AlgorithmRegistration.cpp Algorithm.cpp

obj = $(src:.cpp=.o)
CC_FLAGS = -std=c++11 -g -Wall -O2 -pedantic -pthread
CXXFLAGS = -std=c++11 -g -Wall -O2 -pedantic -pthread -fPIC
CXX=g++


#AbstractAlgorithm.h is part of BOTH

#AlgorithmRegistrar.h is part of the simulation
#AlgorithmRegistrar.cpp is part of the simulation

#AlgorithmRegistration.h is part of BOTH
#AlgorithmRegistration.cpp is part of the simulation


.cc.o:
	$(CXX) -ggdb -c $(CC_FLAGS) -o $@ $< 

# may add boost libraries here
LD_FLAGS = -ldl -fPIC

_312908205_A.o: _312908205_A.cpp
	$(CXX) -c _312908205_A.cpp $(CC_FLAGS) -fPIC

312908205_A_.so: _312908205_A.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,312908205_A_.so -o 312908205_A_.so _312908205_A.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

_312908205_B.o: _312908205_B.cpp
	$(CXX) -c _312908205_B.cpp $(CC_FLAGS) -fPIC

312908205_B_.so: _312908205_B.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,312908205_B_.so -o 312908205_B_.so _312908205_B.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

_312908205_C.o: _312908205_C.cpp
	$(CXX) -c _312908205_C.cpp $(CC_FLAGS) -fPIC

312908205_C_.so: _312908205_C.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,312908205_C_.so -o 312908205_C_.so _312908205_C.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

#_312908205_A

# _306543083_G.o: _306543083_G.cpp
# 	$(CXX) -c _306543083_G.cpp $(CC_FLAGS) -fPIC

# 306543083_G_.so: _306543083_G.o Point.o Algorithm.o my_make_unique.h
# 	$(CXX) -shared -Wl,-soname,306543083_G_.so -o 306543083_G_.so _306543083_G.o Point.o Algorithm.o $(LD_FLAGS)

# _306543083_N.o: _306543083_N.cpp
# 	$(CXX) -c _306543083_N.cpp $(CC_FLAGS) -fPIC

# 306543083_N_.so: _306543083_N.o Point.o Algorithm.o my_make_unique.h
# 	$(CXX) -shared -Wl,-soname,306543083_N_.so -o 306543083_N_.so _306543083_N.o Point.o Algorithm.o $(LD_FLAGS)

score_formula.o: score_formula.cpp
	$(CXX) -c score_formula.cpp $(CC_FLAGS) -fPIC

score_formula.so: score_formula.o
	$(CXX) -shared -Wl,-soname,score_formula.so -o score_formula.so

simulator: $(obj)
	$(CXX) -rdynamic -o $@ $^ $(CC_FLAGS) $(LD_FLAGS)

# algs = 306543083_G_.so 306543083_N_.so
algs = 312908205_A_.so 312908205_B_.so 312908205_C_.so
scr = score_formula.so

algorithms: $(algs)
all: simulator $(algs) $(scr)

.PHONY: clean
clean:
	rm -f *.so *.o simulator
  
