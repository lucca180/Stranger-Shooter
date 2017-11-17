CC=gcc

CFLAGS=-g -Wall -pedantic -D_GNU_SOURCE=1 -D_REENTRANT -lm
IMAGE_FLAGS=-lSDL2_image
MIXER_FLAGS=-lSDL2_mixer
SFLAGS=-lSDL2
SOURCES=main.c funcoes.c globais.c telas.c
OBJECTS=main.o funcoes.o globais.o telas.o
BINARIES=main

all: $(BINARIES)

StrangerShooter: main.o includes/funcoes.o includes/globais.o includes/telas.o
	$(CC) -o main main.o includes/funcoes.o includes/globais.o includes/telas.o $(CFLAGS) $(SFLAGS) $(LFLAGS) $(IFLAGS) $(IMAGE_FLAGS) $(MIXER_FLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)
	
funcoes.o: includes/funcoes.c
	$(CC) -c includes/funcoes.c $(CFLAGS)

telas.o: includes/telas.c
	$(CC) -c includes/telas.c $(CFLAGS)

globais.o: includes/globais.c
	$(CC) -c includes/globais.c $(CFLAGS)

clean:
	rm -rf *.o *.exe *.bak *.c~ $(BINARIES) core a.out

