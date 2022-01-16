CC=g++
SRCDIR=./src
PONG_SRC=./games/Ping-Pong/src
outputDir=./build
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES=-I./include

all: test pong

test: tests.o logger.o renderwindow.o values.o timestep.o utils.o math.o
	mkdir -p build
	$(CC) $^ $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/test

run_tests: test
	./build/test

pong: pong_main.o logger.o renderwindow.o timestep.o entity.o utils.o audio.o
	mkdir -p build
	rsync -av ./games/Ping-Pong/res ./build/
	$(CC) $^ $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/pong

pong_main.o: $(PONG_SRC)/pong_entry.cpp
	$(CC) -c $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o pong_main.o


audio.o: $(SRCDIR)/audio.cpp
	$(CC) -c $(INCLUDES) $^ -o audio.o

entity.o: $(SRCDIR)/entity.cpp
	$(CC) -c $(INCLUDES) $^ -o entity.o

logger.o: $(SRCDIR)/logger.cpp
	$(CC) -c $^ -o logger.o

tests.o: $(SRCDIR)/tests.cpp
	$(CC) -c $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o tests.o

math.o: $(SRCDIR)/math.cpp
	$(CC) -c $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o math.o

renderwindow.o: $(SRCDIR)/renderwindow.cpp
	$(CC) -c $(INCLUDES) $(WarningFlags) $^ -o renderwindow.o

timer.o: $(SRCDIR)/timer.cpp
	$(CC) -c $(INCLUDES) $(WarningFlags) $^ -o timer.o

timestep.o: $(SRCDIR)/timestep.cpp
	$(CC) -c $(INCLUDES) $(WarningFlags) $^ -o timestep.o

utils.o: $(SRCDIR)/utils.cpp
	$(CC) -c $(INCLUDES) $(WarningFlags) $^ -o utils.o

values.o: $(SRCDIR)/values.cpp
	$(CC) -c $(INCLUDES) $(WarningFlags) $^ -o values.o



.PHONY: clean
clean:
	rm -f *.o log.txt
	rm -rf $(outputDir)
