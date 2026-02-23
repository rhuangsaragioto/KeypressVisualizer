CC = g++
CFLAGS = --std=c++20 -Wall -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

DEPS = KeypressVisualizer.hpp

OBJECTS = KeypressVisualizer.o

.PHONY: all clean KeypressVisualizer

all: KeypressVisualizer

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

KeypressVisualizer: main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f *.o KeypressVisualizer

lint:
	cpplint *.cpp *.hpp