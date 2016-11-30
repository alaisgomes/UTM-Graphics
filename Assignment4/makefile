# to compile, type "make" in terminal
# to execute, type "./simple" in terminal, after compilation

GLFLAGS = -lglut -lGL -lGLU -lX11 -lm 

all: main clean

main: cubes.o
	g++ cubes.o -o cubes $(GLFLAGS)

simple.o: cubes.cpp
	g++ -c cubes.cpp 

clean:
	rm -f *.o main
