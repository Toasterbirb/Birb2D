CC=g++
outputDir=./build
CFLAGS=-O3
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx

APP="application"


all: application

application: main.o
	mkdir -p build
	cp -av ./res ./build/
	$(CC) $^ -lbirb2d $(CFLAGS) $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/$(APP)

appimage: application
	mkdir -p $(outputDir)/AppDir/usr/bin
	mkdir -p $(outputDir)/AppDir/usr/share/$(APP)
	cp -v $(outputDir)/$(APP) $(outputDir)/AppDir/usr/bin/
	cp -av $(outputDir)/res $(outputDir)/AppDir/usr/share/$(APP)/
	cd $(outputDir) ; appimage-builder --generate

appimage-build:
	cp -v $(outputDir)/$(APP) $(outputDir)/AppDir/usr/bin/
	cd $(outputDir) ; appimage-builder --skip-tests --recipe AppImageBuilder.yml

%.o: ./src/%.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -rf build
	rm -f *.o
