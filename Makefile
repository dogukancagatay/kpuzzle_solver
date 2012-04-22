CC=g++
CFLAGS=-O2 -c -Wall
LDFLAGS=-O2
MAIN_S=kpuzzle_main.cpp
EXEC=kpuzzle_solver

EXEC_D=kpuzzle_main.o 
OBJS=$(EXEC_D) 

$(EXEC): $(OBJS) 
	    $(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

kpuzzle_main.o: kpuzzle_main.cpp kpuzzle.hpp kpuzzle_algorithms.hpp 
	    $(CC) $(CFLAGS) $(MAIN_S)

clean:
	    rm $(EXEC_D) $(EXEC)
