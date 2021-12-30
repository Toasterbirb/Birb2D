CC=g++
SRCDIR=./src
PONG_SRC=./games/Ping-Pong/src
outputDir=./build
binary=birb2d
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCLUDES=-I./include

all: test pong

test: tests.o logger.o renderwindow.o values.o timestep.o
	mkdir -p build
	$(CC) $^ $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/test

run_tests: test
	./build/test

pong: pong_main.o logger.o renderwindow.o timestep.o
	mkdir -p build
	$(CC) $^ $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/pong

pong_main.o: $(PONG_SRC)/main.cpp
	$(CC) -c $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o pong_main.o

tests.o: $(SRCDIR)/tests.cpp
	$(CC) -c $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o tests.o

logger.o: $(SRCDIR)/logger.cpp
	$(CC) -c $^ -o logger.o

renderwindow.o: $(SRCDIR)/renderwindow.cpp
	$(CC) -c $(INCLUDES) -lSDL2 -lSDL2_image -lSDL2_ttf $(WarningFlags) $^ -o renderwindow.o

values.o: $(SRCDIR)/values.cpp
	$(CC) -c $(INCLUDES) -lSDL2 $(WarningFlags) $^ -o values.o

timestep.o: $(SRCDIR)/timestep.cpp
	$(CC) -c $(INCLUDES) -lSDL2 $(WarningFlags) $^ -o timestep.o


.PHONY: clean
clean:
	rm -f *.o log.txt
	rm -rf $(outputDir)
