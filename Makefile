CC=g++
SRCDIR=./src
outputDir=./build
binary=birb2d
WarningFlags=-Wpedantic -pedantic -Wall -Wextra
SDL_FLAGS=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: final

builddir:
	mkdir -p ${outputDir}

audio:
	${CC} -c -g ${SRCDIR}/audio.cpp -lSDL2_mixer ${WarningFlags} -o ${outputDir}/audio.o

entity:
	${CC} -c -g ${SRCDIR}/entity.cpp ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/entity.o

font:
	${CC} -c -g ${SRCDIR}/font.cpp -lSDL2_ttf ${WarningFlags} -o ${outputDir}/font.o

renderwindow:
	${CC} -c -g ${SRCDIR}/renderwindow.cpp ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/renderwindow.o

widgets:
	${CC} -c -g ${SRCDIR}/widgets.cpp ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/widgets.o

values:
	${CC} -c -g ${SRCDIR}/values.cpp -lSDL2 ${WarningFlags} -o ${outputDir}/values.o

logger:
	${CC} -c -g ${SRCDIR}/logger.cpp ${WarningFlags} -o ${outputDir}/logger.o

doctest:
	${CC} -c -g ${SRCDIR}/tests.cpp ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/tests.o

editor_main: 
	${CC} -c -g ${SRCDIR}/editor.cpp ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/editor.o

test: builddir audio entity font renderwindow widgets values logger doctest 
	${CC} -g ${outputDir}/*.o ${SDL_FLAGS} -o ${outputDir}/${binary}_test
	cd ${outputDir} ; ./${binary}_test

final: builddir audio entity font renderwindow widgets values logger editor_main
	${CC} -g ${outputDir}/*.o ${SDL_FLAGS} ${WarningFlags} -o ${outputDir}/editor

win: clean builddir
	mkdir -p ${outputDir}/win
	x86_64-w64-mingw32-g++ -DPLATFORM_WIN ./src/audio.cpp ./src/entity.cpp ./src/font.cpp ./src/renderwindow.cpp ./src/widgets.cpp ./src/values.cpp ./src/tests.cpp ${SDL_FLAGS} \
		-I./vendor/SDL2_win/SDL2/x86_64-w64-mingw32/include \
		-I./vendor/SDL2_win/SDL2_image-2.0.5/x86_64-w64-mingw32/include \
		-I./vendor/SDL2_win/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include \
		-I./vendor/SDL2_win/SDL2_ttf-2.0.15/x86_64-w64-mingw32/include \
		-L./vendor/SDL2_win/SDL2/x86_64-w64-mingw32/lib \
		-L./vendor/SDL2_win/SDL2_image-2.0.5/x86_64-w64-mingw32/lib \
		-L./vendor/SDL2_win/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib \
		-L./vendor/SDL2_win/SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib \
		-L./vendor/mingw-w64-dlls-4.9.2/ \
		-static-libgcc \
		-static-libstdc++ \
		-o ${outputDir}/win/editor_win.exe
	cp ./vendor/SDL2_win/SDL2/x86_64-w64-mingw32/bin/*.dll ${outputDir}/win/
	cp ./vendor/SDL2_win/SDL2_ttf-2.0.15/x86_64-w64-mingw32/bin/*.dll ${outputDir}/win/
	cp ./vendor/SDL2_win/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/*.dll ${outputDir}/win/
	cp ./vendor/SDL2_win/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/*.dll ${outputDir}/win/
	cp ./vendor/mingw-w64-dlls-4.9.2/*.dll ${outputDir}/win/

run:
	cd ${outputDir} && ./editor

clean:
	rm -rf ${outputDir}
