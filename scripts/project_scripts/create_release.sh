#!/bin/bash
set -e

# Fetch the program name from he CMakeLists file
PROGRAM_NAME=$(awk -F' ' '/^set\(PROGRAM_NAME/ { print $2 }' CMakeLists.txt | tr -d ')')

if [ -f ./win_build.sh ]
then
	# Ask if a windows build should also be generated
	read -p "Compile for Windows? [y/N]: " WIN_BUILD_ENABLED
fi

case $WIN_BUILD_ENABLED in
	y|Y)
		WIN_BUILD_ENABLED=y

		if [ -n $(which distrobox) ]
		then
			read -p "Use distrobox for the windows build? [y/N]: " USE_DISTROBOX

			case $USE_DISTROBOX in
				y|Y) USE_DISTROBOX=y ;;
				*) USE_DISTROBOX=n ;;
			esac
		fi
		;;


	*) WIN_BUILD_ENABLED=n ;;
esac


# Compile for linux
mkdir -p build
cd build && cmake .. -DCMAKE_BUILD_TYPE=Release -DRELEASE=On -DUTILS=Off -DTESTS=Off && make -j$(nproc)
cd ..

# Compile for windows
if [ "$WIN_BUILD_ENABLED" == "y" ]
then
	if [ "$USE_DISTROBOX" == "y" ]
	then
		distrobox enter birb2d_win_build_env -- ./win_build.sh
	else
		./win_build.sh
	fi
fi

echo "Building finished! Packing up..."
LINUX_DIST_PATH="${PROGRAM_NAME}_linux"
WINDOWS_DIST_PATH="${PROGRAM_NAME}_windows"
rm -rfv ./build/dist
mkdir -pv ./build/dist/${LINUX_DIST_PATH}
[ "$WIN_BUILD_ENABLED" == "y" ] && mkdir -pv ./build/dist/${WINDOWS_DIST_PATH}

# Strip debug symbols
echo "Stripping debug symbols from binaries..."
strip -v ./build/${PROGRAM_NAME}
strip -v ./build_win/${PROGRAM_NAME}.exe

# Copy over linux build files
cp -v ./build/${PROGRAM_NAME} ./build/dist/${LINUX_DIST_PATH}/
cp -rv ./build/res ./build/dist/${LINUX_DIST_PATH}/

# Copy over windows build files
if [ "$WIN_BUILD_ENABLED" == "y" ]
then
	cp -v ./build_win/${PROGRAM_NAME}.exe ./build/dist/${WINDOWS_DIST_PATH}/
	cp -rv ./build_win/res ./build/dist/${WINDOWS_DIST_PATH}/
fi

# Create tarball for linux and a zip file for windows users
tar -C ./build/dist -cavzf ./build/dist/${LINUX_DIST_PATH}.tar.xz ./${LINUX_DIST_PATH}
[ "$WIN_BUILD_ENABLED" == "y" ] && ( cd ./build/dist ; zip -r ./${WINDOWS_DIST_PATH}.zip ./${WINDOWS_DIST_PATH} )

echo -e "\n\e[1mRelease files created:\e[0m"
echo "./build/dist/${LINUX_DIST_PATH}.tar.xz"
[ "$WIN_BUILD_ENABLED" == "y" ] && echo "./build/dist/${WINDOWS_DIST_PATH}.zip"
