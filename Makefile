##
# Mandelbrot set
#

CC     = g++

CFLAGS = -c -O3


all: mandelbrot

mandelbrot: mandelbrot.o
	$(CC) Obj/mandelbrot.o -lsfml-window -lsfml-graphics -lsfml-system -lm -o mandelbrot

mandelbrot.o: Src/mandelbrot.cpp
	$(CC) $(CFLAGS) Src/mandelbrot.cpp -o Obj/mandelbrot.o

clear:
	rm -rf *.o mandelbrot

#end

