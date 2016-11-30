# Makefile to build the flag program
# Jeremy Greenburg
# September 9th

FLAGS = -lglut -lGL -lGLU -lX11 -lm 
COMPILER = g++
TARGET = walker

all: $(TARGET)

$(TARGET): main.o Walker.o
	$(COMPILER) $(OUTPUT) main.o Walker.o $(FMOD) $(FLAGS)

main.o: main.cpp
	$(COMPILER) -c main.cpp -Wall

Walker.o: Walker.cpp Walker.h
	$(COMPILER) -c Walker.cpp -Wall;

clean:
	rm *~ *o
