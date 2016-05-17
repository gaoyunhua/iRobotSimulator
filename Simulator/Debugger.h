
#ifndef SIMULATOR_DEBUGGER_H
#define SIMULATOR_DEBUGGER_H

#define DEBUG 1

#define PRINT_DEBUG(msg) do{	\
    if (DEBUG)				\
	    cout << msg << endl;	\
    }while (0)

#endif //SIMULATOR_DEBUGGER_H
