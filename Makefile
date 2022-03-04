CC=g++
SRCDIR=./src
TEST_SRCDIR=./src/tests
outputDir=./build
CFLAGS=-fPIC -O3 -g -std=c++17
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES=-I./include
LIBFILE=libbirb2d.so

all: test docs engine_lib run_tests

docs:
	doxygen ./doxygen_config

test: audio.o filesystem.o entity.o logger.o math.o physics.o renderwindow.o timer.o timestep.o utils.o values.o doctest.o audio_test.o entity_test.o filesystem_test.o logger_test.o math_test.o physics_test.o renderwindow_test.o timer_test.o utils_test.o values_test.o
	mkdir -p build
	cp -r ./res $(outputDir)/
	$(CC) $^ $(CFLAGS) $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/test

run_tests: test
	./build/test

run_quick_tests: test
	./build/test -tce="*rendering*,*audio*,*timer*"

engine_lib: filesystem.o audio.o entity.o logger.o math.o renderwindow.o physics.o timer.o timestep.o ui.o utils.o values.o
	mkdir -p build
	g++ -shared -g $(CFLAGS) $(SDL_FLAGS) -o $(outputDir)/$(LIBFILE) $^

static_engine_lib: filesystem.o audio.o entity.o logger.o math.o renderwindow.o physics.o timer.o timestep.o ui.o utils.o values.o
	mkdir -p build
	ar -crs $(outputDir)/libbirb2d.a $^

install: engine_lib
	cp $(outputDir)/$(LIBFILE) /usr/lib/
	mkdir -p /usr/local/include/birb2d
	cp ./include/* /usr/local/include/birb2d/
	ldconfig

uninstall:
	rm -f /usr/lib/$(LIBFILE)
	rm -rf /usr/local/include/birb2d
	ldconfig

# Engine code
%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^

# Test code
%.o: $(TEST_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^



.PHONY: clean
clean:
	rm -f *.o log.txt
	rm -rf $(outputDir)
	rm -rf docs
	rm -rf *.AppDir
	rm -f *.AppImage
