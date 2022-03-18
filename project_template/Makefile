CC=g++
outputDir=./build
CFLAGS=-O3
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx

all: application

application: main.o
	mkdir -p build
	rsync -av ./res ./build/
	$(CC) $^ -lbirb2d $(CFLAGS) $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/application

%.o: ./src/%.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf build
	rm -f *.o
