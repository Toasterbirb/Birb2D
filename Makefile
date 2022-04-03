CC=g++
SRCDIR=./src
TEST_SRCDIR=./src/tests
outputDir=./build
CFLAGS=-fPIC -g -std=c++17
WarningFlags=-Wpedantic -Wall -Wextra -Wfloat-equal
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES=-I./include
LIBFILE=libbirb2d.so
DESTDIR=/usr

LIB_SRC:=$(wildcard $(SRCDIR)/*.cpp)
LIB_OBJ_SRC:=$(LIB_SRC:.cpp=.o)
LIB_OBJ=$(subst src/,,$(LIB_OBJ_SRC))

TEST_SRC:=$(wildcard $(TEST_SRCDIR)/*.cpp)
TEST_OBJ_SRC:=$(TEST_SRC:.cpp=.o)
TEST_OBJ=$(subst src/tests,,$(TEST_OBJ_SRC))

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
	mkdir -p $(DESTDIR)/lib
	mkdir -p $(DESTDIR)/include/birb2d
	rm -f $(DESTDIR)/lib/libbirb2d.a
	cp $(outputDir)/$(LIBFILE) $(DESTDIR)/lib/
	cp ./include/*.hpp $(DESTDIR)/include/birb2d/
	ldconfig

install_static: static_engine_lib
	mkdir -p $(DESTDIR)/lib
	mkdir -p $(DESTDIR)/include/birb2d
	rm -f $(DESTDIR)/lib/$(LIBFILE)
	cp $(outputDir)/libbirb2d.a $(DESTDIR)/lib/
	cp ./include/*.hpp $(DESTDIR)/include/birb2d/
	ldconfig

uninstall:
	rm -f $(DESTDIR)/lib/$(LIBFILE)
	rm -f $(DESTDIR)/lib/libbirb2d.a
	rm -rf $(DESTDIR)/include/birb2d
	ldconfig

uninstall_lib:
	rm -f $(DESTDIR)/lib/$(LIBFILE)
	rm -f $(DESTDIR)/lib/libbirb2d.a
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
