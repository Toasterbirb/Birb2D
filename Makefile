CC=g++
SRCDIR=./src
outputDir=./build
CFLAGS=-fPIC -O2
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES=-I./include
LIBFILE=libbirb2d.so

all: test engine_lib

test: tests.o logger.o renderwindow.o values.o timestep.o utils.o math.o
	mkdir -p build
	$(CC) $^ $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/test

run_tests: test
	./build/test

engine_obj: audio.o entity.o logger.o math.o renderwindow.o timer.o timestep.o utils.o values.o
	mkdir -p build
	ld -r $^ -o $(outputDir)/birb2d.o

engine_lib: audio.o entity.o logger.o math.o renderwindow.o timer.o timestep.o utils.o values.o
	mkdir -p build
	g++ -shared $(SDL_FLAGS) -o $(outputDir)/$(LIBFILE) $^

install: engine_lib
	cp $(outputDir)/$(LIBFILE) /usr/lib/
	mkdir -p /usr/local/include/birb2d
	cp ./include/* /usr/local/include/birb2d/

uninstall:
	rm -f /usr/lib/$(LIBFILE)
	rm -rf /usr/local/include/birb2d

audio.o: $(SRCDIR)/audio.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^ -o audio.o

entity.o: $(SRCDIR)/entity.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^ -o entity.o

logger.o: $(SRCDIR)/logger.cpp
	$(CC) -c $(CFLAGS) $^ -o logger.o

tests.o: $(SRCDIR)/tests.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o tests.o

math.o: $(SRCDIR)/math.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(SDL_FLAGS) $(WarningFlags) $^ -o math.o

renderwindow.o: $(SRCDIR)/renderwindow.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(WarningFlags) $^ -o renderwindow.o

timer.o: $(SRCDIR)/timer.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(WarningFlags) $^ -o timer.o

timestep.o: $(SRCDIR)/timestep.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(WarningFlags) $^ -o timestep.o

utils.o: $(SRCDIR)/utils.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(WarningFlags) $^ -o utils.o

values.o: $(SRCDIR)/values.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $(WarningFlags) $^ -o values.o



.PHONY: clean
clean:
	rm -f *.o log.txt
	rm -rf $(outputDir)
