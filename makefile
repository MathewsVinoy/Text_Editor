CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`

all: app

app: main.c
	$(CC) -o app main.c $(CFLAGS)

clean:
	rm -f app
