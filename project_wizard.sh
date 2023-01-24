#!/bin/bash
set -e

echo -e "\033[32mWelcome to the Birb2D project wizard!\033[0m"
EXEC_PATH="$(dirname $0)"

# Make sure the user has all of the required software installed
MISSING_PROGRAMS=""
function check_program()
{
	which $1 &>/dev/null || MISSING_PROGRAMS="$MISSING_PROGRAMS\n - $1"
}

check_program "bash"
check_program "cmake"
check_program "g++"
check_program "gcc"
check_program "make"

[ -n "$MISSING_PROGRAMS" ] && echo -e "Warning! The following required programs are missing:\n${MISSING_PROGRAMS}\n\nYou might be able to create a project without them,\nbut things might not work as expected"

function yes_no_prompt()
{
	if [ "$2" == "y" ]
	then
		read -p "$1 [Y/n]: " PROMPT_RESULT
		case $PROMPT_RESULT in
			n|N) echo "false" ;;
			*) echo "true" ;;
		esac
	else
		read -p "$1 [y/N]: " PROMPT_RESULT
		case $PROMPT_RESULT in
			y|Y) echo "true" ;;
			*) echo "false" ;;
		esac
	fi
}

function menu()
{
	echo -e "\n$1" > /dev/stderr
	shift

	IFS=$(echo -e "\n\b")
	let counter=1
	for i in $@
	do
		echo "$counter) $i" > /dev/stderr
		let counter+=1
	done
	read -p "> " MENU_RESULT
	echo $MENU_RESULT
}

# Some key project details
read -p "Project name: " PROJECT_NAME
[ -z "$PROJECT_NAME" ] && echo "Can't continue without a project name!" && exit 1
PROJECT_NAME=$(sed 's/[[:space:]]/_/g' <<< $PROJECT_NAME)

read -e -p "Project path: " PROJECT_PATH
[ -z "$PROJECT_PATH" ] && echo "Can't continue without project path!" && exit 1
PROJECT_PATH="$(sed "s|~|$HOME|g" <<< $PROJECT_PATH)"

# Engine source code handling
USE_SYMLINK=$(yes_no_prompt "Symlink to Birb2D instead of using git submodules" "n")
if [ "$USE_SYMLINK" == "true" ]
then
	read -e -p "Path to Birb2D source code: " BIRB2D_SOURCE_PATH
	BIRB2D_SOURCE_PATH="$(sed "s|~|$HOME|g" <<< $BIRB2D_SOURCE_PATH)"
else
	BIRB2D_REPO_URL="https://github.com/toasterbirb/birb2d"
	CUSTOM_BIRB2D_REPO=$(yes_no_prompt "Clone Birb2D from a custom repository" "n")
	if [ "$CUSTOM_BIRB2D_REPO" == "true" ]
	then
		read -p "Repository URL: " CUSTOM_BIRB2D_REPO_URL
		BIRB2D_REPO_URL="$CUSTOM_BIRB2D_REPO_URL"
	fi
fi

USE_DISTCC=$(yes_no_prompt "Use distcc and ccache to help with compiling times" "n")

# Basic game project details
read -p "Game window title [Game]: " GAME_WINDOW_TITLE
[ -z "$GAME_WINDOW_TITLE" ] && GAME_WINDOW_TITLE="Game"

RESIZABLE_WINDOW=$(yes_no_prompt "Default to resizable window" "n")

read -p "Default window resolution [1280x720]: " GAME_WINDOW_RESOLUTION
[ -z "$GAME_WINDOW_RESOLUTION" ] && GAME_WINDOW_RESOLUTION="1280x720"

echo -e "\n\e[4mSummary\e[0m:"
echo "Project name: $PROJECT_NAME"
echo "Project path: $PROJECT_PATH"
if [ "$USE_SYMLINK" == "true" ]
then
	echo "Birb2D source code will be symlinked from $BIRB2D_SOURCE_PATH"
else
	echo "Birb2D source code URL: $BIRB2D_REPO_URL"
fi
echo "Use distcc + ccache: $USE_DISTCC"
printf "\n"
echo "Game window title: $GAME_WINDOW_TITLE"
echo "Default window resolution: $GAME_WINDOW_RESOLUTION"
echo "Resizable window: $RESIZABLE_WINDOW"

printf "\n"
CONTINUE=$(yes_no_prompt "Create project with these settings?" "n")

[ "$CONTINUE" == "false" ] && echo "Mission aborted" && exit 0

echo -e "Starting project creation!\nWarning: This might take a while, so go take a walk or drink some coffee in the meantime"
sleep 2

# Start creating the project
echo "Copying the project skeleton..."
mkdir -p $PROJECT_PATH
cp -rL $EXEC_PATH/project_skeleton/* $PROJECT_PATH/

# Create any missing directories
mkdir -p $PROJECT_PATH/include $PROJECT_PATH/res

echo "Setting project values..."
sed -i "s/<PROJECT_NAME>/$PROJECT_NAME/" $PROJECT_PATH/CMakeLists.txt
sed -i "s/<GAME_WINDOW_TITLE>/$GAME_WINDOW_TITLE/" $PROJECT_PATH/src/main.cpp
sed -i "s/<WINDOW_RES_X>/$(cut -d'x' -f1 <<< $GAME_WINDOW_RESOLUTION)/" $PROJECT_PATH/src/main.cpp
sed -i "s/<WINDOW_RES_Y>/$(cut -d'x' -f2 <<< $GAME_WINDOW_RESOLUTION)/" $PROJECT_PATH/src/main.cpp
sed -i "s/<RESIZABLE_WINDOW>/$RESIZABLE_WINDOW/" $PROJECT_PATH/src/main.cpp

if [ "$USE_SYMLINK" == "true" ]
then
	ln -sv "$BIRB2D_SOURCE_PATH" $PROJECT_PATH/birb2d
else
	echo "Cloning Birb2D"
	git init $PROJECT_PATH
	( cd $PROJECT_PATH ; git submodule add --depth 1 $BIRB2D_REPO_URL ; cd $PROJECT_PATH/birb2d ; git submodule update --init --recursive )
fi

# Prepare a build
mkdir -p $PROJECT_PATH/build
cd $PROJECT_PATH/build
if [ "$USE_DISTCC" ]
then
	cmake -DDISTCC=on -DCMAKE_C_COMPILER_LAUNCHER="ccache;distcc" -DCMAKE_CXX_COMPILER_LAUNCHER="ccache;distcc" .. && make -j$(distcc -j)
else
	cmake .. && make -j$(nproc)
fi

echo "Project created successfully to $PROJECT_PATH"
