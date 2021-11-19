CC=g++
SRCDIR=./src
outputDir=./build
binary=birb2d
FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: final

builddir:
	mkdir -p ${outputDir}

audio:
	${CC} -c -g ${SRCDIR}/audio.cpp -lSDL2_mixer -o ${outputDir}/audio.o

entity:
	${CC} -c -g ${SRCDIR}/entity.cpp ${FLAGS} -o ${outputDir}/entity.o

font:
	${CC} -c -g ${SRCDIR}/font.cpp -lSDL2_ttf -o ${outputDir}/font.o

renderwindow:
	${CC} -c -g ${SRCDIR}/renderwindow.cpp ${FLAGS} -o ${outputDir}/renderwindow.o

widgets:
	${CC} -c -g ${SRCDIR}/widgets.cpp ${FLAGS} -o ${outputDir}/widgets.o

doctest:
	${CC} -c -g ${SRCDIR}/tests.cpp ${FLAGS} -o ${outputDir}/tests.o

editor_main: 
	${CC} -c -g ${SRCDIR}/editor.cpp ${FLAGS} -o ${outputDir}/editor.o

test: builddir audio entity font renderwindow widgets doctest 
	${CC} -g ${outputDir}/*.o ${FLAGS} -o ${outputDir}/${binary}_test

final: builddir audio entity font renderwindow widgets editor_main
	${CC} -g ${outputDir}/*.o ${FLAGS} -o ${outputDir}/editor

clean:
	rm -rf ${outputDir}
