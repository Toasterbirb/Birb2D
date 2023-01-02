# Birb2D
![Test workflow](https://github.com/toasterbirb/birb2d/actions/workflows/run_tests.yml/badge.svg)
[![Windows build](https://github.com/Toasterbirb/Birb2D/actions/workflows/windows_build.yml/badge.svg)](https://github.com/Toasterbirb/Birb2D/actions/workflows/windows_build.yml)

**Project compatibility**

[![Void](https://github.com/Toasterbirb/Birb2D/actions/workflows/void_compat.yml/badge.svg)](https://github.com/Toasterbirb/Birb2D/actions/workflows/void_compat.yml)
[![Tic-Tac-Toe](https://github.com/Toasterbirb/Birb2D/actions/workflows/tic-tac-toe_compat.yml/badge.svg)](https://github.com/Toasterbirb/Birb2D/actions/workflows/tic-tac-toe_compat.yml)


Birb2D is a small and delicate 2D game engine made as a learning project.

Birb2D is not meant to be *production* quality, but there's a chance it can be used to make some games. Expect segfaults and all that usual stuff that come with newbie hobbyist C++ projects. If anyone ever picks this thing up and actually does something with it, definitely send it [my](https://github.com/Toasterbirb) way. I'd love to see it happen. Also any ideas or suggestions are welcome. Just know the scope, I'm not remaking Unity or Unreal Engine.

## Projects made with Birb2D
- [Flappy Birb](https://github.com/Toasterbirb/Flappy-Birb)
- [Pong](https://github.com/Toasterbirb/Pong)
- [SeedSplit](https://github.com/Toasterbirb/SeedSplit)
- [Breakout](https://github.com/Toasterbirb/Breakout)
- [LD50.exe (Ludum Dare game)](https://ldjam.com/events/ludum-dare/50/ld50-exe)
- [The Diamond Heist (Ludum Dare game)](https://ldjam.com/events/ludum-dare/51/the-diamond-heist)
- [Void](https://github.com/Toasterbirb/Void)
- [Tic-Tac-Toe](https://github.com/Toasterbirb/tic-tac-toe)

## External libraries
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- SDL2_gfx
- [doctest](https://github.com/doctest/doctest) (included as a headerfile)
- [cppcodec](https://github.com/tplgy/cppcodec)
- [json](https://github.com/nlohmann/json) (included as a headerfile)
- [libzip](https://github.com/nih-at/libzip)
- [microprofile](https://github.com/jonasmr/microprofile)

## Building
Refer to [this](https://github.com/Toasterbirb/Birb2D/wiki/Setup) wiki page

## What works so far
Birb2D can already do something. You can draw pictures, polygons and other shapes and check for collisions etc. Also sound, buttons, a basic scene system and some basic math stuff is there. Physics engine is still completely missing. Also the documentation is quite lacking

## Note to Windows users
There's a [script](https://github.com/Toasterbirb/Birb2D/blob/master/scripts/win_build.sh) that can help with creating windows builds. Everything in the engine *should* compile, but the tests won't compile due to some issue with mingw and doctest. Builds have been tested with [wine](https://www.winehq.org/) on Linux and some brave people have also gotten them to run on a native windows installation.

Compiling Birb2D on window is still a bit problematic since it requires installing mingw and several other tools. Also since the tests don't work on windows, native engine development is pretty difficult without the use of WSL. This is still a non-issue though since most, if not all, active contributors are Linux users. It's good enough that there is at least some way to create windows binaries for distribution since majority of the operating system market share is still in the windows camp.

## Credits
Some notable people who have donated code to Birb2D or helped with ideas/issues. If you think you should be included here, shoot me a message ʕ •ᴥ•ʔ
- [Josh Santos](https://github.com/thatnerdjosh)
- [Quartzi](https://github.com/realQuartzi)
