CC=g++
CFLAGS= -O3 -ffast-math -Wall -std=c++11

all: shaders
	$(CC) $(CFLAGS) -c main.cpp
	$(CC) $(CFLAGS)	shaders.o  main.o -o test -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -I../glfw/include/GLFW -L../glfw/src -lglfw3
	rm *.o
shaders:
	$(CC) $(CFLAGS) -c shaders.cpp
run: all
	./test
