CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
INCLUDES = -Iwindow

all: app

app: main.o window/mainwindow.o
	$(CC) -o app main.o window/mainwindow.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c -o main.o

window/mainwindow.o: window/mainwindow.c
	$(CC) $(CFLAGS) $(INCLUDES) -c window/mainwindow.c -o window/mainwindow.o

clean:
	rm -f *.o window/*.o app
