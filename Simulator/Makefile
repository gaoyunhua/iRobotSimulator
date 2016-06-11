.DEFAULT_GOAL := all

# place here your source files
src = Cleaner.cpp CleanerResult.cpp FileReader.cpp House.cpp Encoder.cpp Montage.cpp Point.cpp Sensor.cpp main.cpp Simulator.cpp ScoreManager.cpp score_formula.cpp AlgorithmRegistrar.cpp AlgorithmRegistration.cpp Montage.cpp Encoder.cpp

obj = $(src:.cpp=.o)
CC_FLAGS = -std=c++11 -g -Wall -O2 -pedantic -pthread
CXXFLAGS = -std=c++11 -g -Wall -O2 -pedantic -pthread -fPIC
CXX=g++

.cc.o:
	$(CXX) -ggdb -c $(CC_FLAGS) -o $@ $< 

# may add boost libraries here
LD_FLAGS = -ldl -fPIC

_306543083_A.o: _306543083_A.cpp
	$(CXX) -c _306543083_A.cpp $(CC_FLAGS) -fPIC

306543083_A_.so: _306543083_A.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,306543083_A_.so -o 306543083_A_.so _306543083_A.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

_306543083_B.o: _306543083_B.cpp
	$(CXX) -c _306543083_B.cpp $(CC_FLAGS) -fPIC

306543083_B_.so: _306543083_B.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,306543083_B_.so -o 306543083_B_.so _306543083_B.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

_306543083_C.o: _306543083_C.cpp
	$(CXX) -c _306543083_C.cpp $(CC_FLAGS) -fPIC

306543083_C_.so: _306543083_C.o Point.o GeneralAlgorithm.o my_make_unique.h HouseMap2.o common.o Location.o
	$(CXX) -shared -Wl,-soname,306543083_C_.so -o 306543083_C_.so _306543083_C.o Point.o GeneralAlgorithm.o HouseMap2.o common.o Location.o $(LD_FLAGS)

score_formula.o: score_formula.cpp
	$(CXX) -c score_formula.cpp $(CC_FLAGS) -fPIC

score_formula.so: score_formula.o
	$(CXX) -shared -Wl,-soname,score_formula.so -o score_formula.so

simulator: $(obj)
	$(CXX) -rdynamic -o $@ $^ $(CC_FLAGS) $(LD_FLAGS)

algs = 306543083_A_.so 306543083_B_.so 306543083_C_.so
scr = score_formula.so

algorithms: $(algs)
all: simulator $(algs) $(scr)

.PHONY: clean
clean:
	rm -f *.so *.o simulator
  
