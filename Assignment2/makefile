# to compile, type "make" in terminal
# to execute, type "./simple" in terminal, after compilation

GLFLAGS = -lglut -lGL -lGLU -lX11 -lm 

all: main clean

main: gasket.o
	g++ gasket.o -o gasket $(GLFLAGS)

simple.o: gasket.cpp
	g++ -c gasket.cpp 

clean:
	rm -f *.o main
