CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=kpuzzle_solver.cpp
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=kpuzzle_solver

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
