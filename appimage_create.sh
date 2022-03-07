#!/bin/bash

output=./birb2d_project.AppDir

function _printHelp()
{
	echo "Usage:"
	echo -e "--project\tSet the Birb2D project directory"
	echo -e "--out\t\tSet the output path for the AppImage [optional]"
	exit 0
}

function _createAppImage()
{
	engine_path=$(pwd)
	echo "Engine path: $engine_path"

	echo "Compiling the engine"
	make -j$(nproc) engine_lib

	echo "Compiling the target project"
	cd $projectPath
	make -j$(nproc)

	# Start building the appimage directory structure to the output path
	cd "$engine_path"
	mkdir -p "$output"
	mkdir -p "$output/usr/bin"
	mkdir -p "$output/usr/share/SeedSplit"
	mkdir -p "$output/usr/lib64"

	# Copy in the Birb2D and SDL2 libraries
	sdlFiles=$(find /usr/lib64 /usr/local/lib64 -name libSDL2*.so)
	cp $sdlFiles "$output/usr/lib64/"
	cp "$engine_path/build/libbirb2d.so" "$output/usr/lib64/"

	# Copy in the game executable and its resources
	cp $projectPath/build/* $output/usr/bin/
	cp -r $projectPath/build/res $output/share/SeedSplit/

	# Get the binary name sneakily with sed
	executable=$(ls $output/usr/bin | sed '/res/d')
	echo "Main executable: $executable"

	# Create AppRun
	echo -e "#!/bin/sh\n \
HERE=\"\$(dirname \"\$(readlink -f \"\${0}\")\")\"\n \
EXEC=\"\${HERE}/usr/bin/$executable\"\n \
exec \"\${EXEC}\""> $output/AppRun

	# Create .desktop file
	echo -e "[Desktop Entry]\n\
Name=$executable\n\
Exec=$executable\n\
Type=Application\n\
Icon=birb
Categories=Game" > $output/birb2d_project.desktop

	chmod +x $output/birb2d_project.desktop
	chmod +x $output/AppRun
}

for i in $@
do
	case "$i" in
		--project)
			shift 2
			projectPath=$1
			;;
		--out)
			shift 1
			output="${1}.AppDir"
			;;
		--help) _printHelp ;;
	esac
done

echo "Project path: $projectPath"

[ -n $projectPath ] && _createAppImage
