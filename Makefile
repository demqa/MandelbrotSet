##
# Mandelbrot set
#

CC     = g++

CFLAGS = -c -O3 -mavx -mavx2

OBJDIR = Obj
MKDIR  = mkdir -p

all: directories mandelbrot

mandelbrot: mandelbrot.o
	$(CC) Obj/mandelbrot.o -lsfml-window -lsfml-graphics -lsfml-system -lm -o mandelbrot

mandelbrot.o: Src/mandelbrot.cpp
	$(CC) $(CFLAGS) Src/mandelbrot.cpp -o Obj/mandelbrot.o

directories:
	$(MKDIR) $(OBJDIR)

clear:
	rm -rf *.o mandelbrot

#end

