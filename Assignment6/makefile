
GLFLAGS = -lglut -lGL -lGLU -lX11 -lm 

all: main clean

main: room.o
	g++ room.o -o room $(GLFLAGS)

simple.o: room.cpp
	g++ -c room.cpp 

clean:
	rm -f *.o main