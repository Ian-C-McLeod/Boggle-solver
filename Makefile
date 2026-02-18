CC = g++
CFLAGS =  -O3 --std=c++2a  -pedantic  -pthread

DEPS = $(wildcard *.hpp)

OBJECTS = trie.o wordfinder.o 

PROGRAM = solver

# Default target to build the programs
all:$(PROGRAM) 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<


# Link the object files to create the final executable

$(PROGRAM) : main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -f *.o $(PROGRAM) test *.a

lint:
	cpplint *.cpp *.hpp 
