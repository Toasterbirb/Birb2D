CC=g++
SRCDIR=./src
TEST_SRCDIR=./src/tests
outputDir=./build
CFLAGS=-fPIC -g -std=c++17
WarningFlags=-Wpedantic -Wall -Wextra -Wfloat-equal
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES=-I./include
LIBFILE=libbirb2d.so

LIB_OBJ=circle.o color.o diagnostics.o filesystem.o graphs.o audio.o entity.o line.o logger.o math.o rect.o renderwindow.o physics.o polygon.o random.o scene.o sceneobject.o timer.o timestep.o ui.o utils.o values.o vector.o
TEST_OBJ=doctest.o audio_test.o circle_test.o color_test.o entity_test.o filesystem_test.o graph_test.o line_test.o logger_test.o math_test.o physics_test.o polygon_test.o random_test.o rect_test.o renderwindow_test.o scene_test.o timer_test.o utils_test.o values_test.o vector_test.o

all: test docs engine_lib run_tests

docs:
	doxygen ./doxygen_config

test: ${LIB_OBJ} ${TEST_OBJ}
	mkdir -p build
	cp -r ./res $(outputDir)/
	$(CC) $^ $(CFLAGS) $(SDL_FLAGS) $(WarningFlags) -o $(outputDir)/test

run_tests: test
	./build/test

run_quick_tests: test
	./build/test -tce="*rendering*,*audio*,*timer*"

run_tests_valgrind: test
	valgrind --leak-check=summary --show-leak-kinds=all ./build/test -tce="*timer*"

run_quick_tests_valgrind: test
	valgrind --leak-check=summary --show-leak-kinds=all ./build/test -tce="*rendering*,*audio*,*timer*"

engine_lib: ${LIB_OBJ}
	mkdir -p build
	$(CC) -shared $(CFLAGS) $(SDL_FLAGS) -o $(outputDir)/$(LIBFILE) $^

static_engine_lib: ${LIB_OBJ}
	mkdir -p build
	ar -crs $(outputDir)/libbirb2d.a $^

install: engine_lib
	rm -f /usr/lib/libbirb2d.a
	cp $(outputDir)/$(LIBFILE) /usr/lib/
	mkdir -p /usr/local/include/birb2d
	cp ./include/* /usr/local/include/birb2d/
	ldconfig

install_static: static_engine_lib
	rm -f /usr/lib/$(LIBFILE)
	cp $(outputDir)/libbirb2d.a /usr/lib/
	mkdir -p /usr/local/include/birb2d
	cp ./include/* /usr/local/include/birb2d/
	ldconfig

uninstall:
	rm -f /usr/lib/$(LIBFILE)
	rm -rf /usr/local/lib64/birb2d_static
	rm -rf /usr/local/include/birb2d
	ldconfig

uninstall_lib:
	rm -f /usr/lib/$(LIBFILE)
	rm -f /usr/lib/libbirb2d.a
	ldconfig

# Engine code
%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^

# Test code
%.o: $(TEST_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $^


docker_build:
	podman build -f ./dockerfiles/fedora-headless.Dockerfile ./ -t birb2d:fedora-headless

.PHONY: clean
clean:
	rm -f *.o log.txt
	rm -rf $(outputDir)
	rm -rf doxygen
	rm -rf *.AppDir
	rm -f *.AppImage
