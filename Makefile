cc=g++
files=./src/* ./playground/src/*
outputDir=./build
binary=game
resources=./playground/res
flags=-lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer

target:
	mkdir -p ${outputDir}
	cp -r ${resources} ${outputDir}/
	${cc} -g ${files} ${flags}  -o ${outputDir}/${binary}_debug

release:
	mkdir -p ${outputDir}
	cp -r ${resources} ${outputDir}/
	${cc} ${files} ${flags} -o ${outputDir}/${binary}

windows:
	mkdir -p ${outputDir}_win
	cp -r ${resources} ${outputDir}_win/
	i686-w64-mingw32-g++ ${files} -I/usr/include/SDL2 -L/usr/i686-w64-mingw32/lib ${flags}  -o ${outputDir}_win/${binary}

clean:
	rm ./${outputDir}
