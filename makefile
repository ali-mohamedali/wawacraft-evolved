CC=g++

CFLAGS=-w -g -fcommon -fpermissive -no-pie
LFLAGS=-lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
LPATHS=-I/usr/include/GL -I/usr/include/GLFW -I/usr/include/glad -L/usr/lib64

SRCDIR=src
LIBDIR=lib
BINDIR=bin
SHDDIR=shd
TEXDIR=tex

BINO=$(BINDIR)/*.o

TARGET=wawacraft-evolved


wawacraft_evolved:
	mkdir -p $(BINDIR)
	make glad stb_image main
	$(CC) $(BINO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

link:
	$(CC) $(BINO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

main: $(SRCDIR)/main.cpp
	$(CC) $(SRCDIR)/main.cpp -o $(BINDIR)/main.o $(CFLAGS) $(LFLAGS) -c

# libraries

glad: $(LIBDIR)/glad.c
	$(CC) $(LIBDIR)/glad.c -o $(BINDIR)/glad.o $(CFLAGS) $(LFLAGS) -c

stb_image: $(LIBDIR)/stb_image.h $(LIBDIR)/stb_image.cpp
	$(CC) $(LIBDIR)/stb_image.cpp -o $(BINDIR)/stb_image.o $(CFLAGS) $(LFLAGS) -c
