# to compile, type "make" in terminal
# to execute, type "./simple" in terminal, after compilation

GLFLAGS = -lglut -lGL -lGLU -lX11 -lm 

all: main clean

main: oldglory.o
	g++ oldglory.o -o oldglory $(GLFLAGS)

simple.o: oldglory.cpp
	g++ -c oldglory.cpp 

clean:
	rm -f *.o main
