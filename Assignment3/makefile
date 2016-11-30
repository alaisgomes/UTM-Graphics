# to compile, type "make" in terminal
# to execute, type "./simple" in terminal, after compilation

GLFLAGS = -lglut -lGL -lGLU -lX11 -lm 

all: main clean

main: paint.o
	g++ paint.o -o paint $(GLFLAGS)

simple.o: paint.cpp
	g++ -c paint.cpp 

clean:
	rm -f *.o main
