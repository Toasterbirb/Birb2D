cc=g++
files=./birb2d/src/* ./src/*
outputDir=./build
binary=game
resources=./res
flags=-Wall -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: builddir debug 

builddir:
	mkdir -p ${outputDir}
	cp -r ${resources} ${outputDir}/

test: builddir
	${cc} -g ${files} ${flags} -o ${outputDir}/${binary}_test

debug: builddir
	${cc} -g ${files} ${flags} -DDOCTEST_CONFIG_DISABLE -o ${outputDir}/${binary}_debug

release: builddir
	${cc} ${files} ${flags} -DDOCTEST_CONFIG_DISABLE -o ${outputDir}/${binary}

windows:
	mkdir -p ${outputDir}_win
	cp -r ${resources} ${outputDir}_win/
	i686-w64-mingw32-g++ ${files} -DDOCTEST_CONFIG_DISABLE -I/usr/include/SDL2 -L/usr/i686-w64-mingw32/lib ${flags}  -o ${outputDir}_win/${binary}

clean:
	rm ./${outputDir}
