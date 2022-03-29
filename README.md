# Birb2D
![Test workflow](https://github.com/toasterbirb/birb2d/actions/workflows/run_tests.yml/badge.svg)

Birb2D is a small and delicate 2D game engine made as a learning project.

Birb2D is not meant to be *production* quality, but there's a chance it can be used to make some games. Expect segfaults and all that usual stuff that come with newbie hobbyist C++ projects. If anyone ever picks this thing up and actually does something with it, definitely send it [my](https://github.com/Toasterbirb) way. I'd love to see it happen. Also any ideas or suggestions are welcome. Just know the scope, I'm not remaking Unity or Unreal Engine.

## Projects made with Birb2D
- [Flappy Birb](https://github.com/Toasterbirb/Flappy-Birb)
- [Pong](https://github.com/Toasterbirb/Pong)
- [SeedSplit](https://github.com/Toasterbirb/SeedSplit)
- [Breakout](https://github.com/Toasterbirb/Breakout)

## External libraries
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- SDL2_gfx
- [doctest](https://github.com/doctest/doctest) (included as a headerfile)

## Building
Refer to [this](https://github.com/Toasterbirb/Birb2D/wiki/Setup) wiki page

## What works so far
Birb2D can already do something. You can draw pictures, polygons and other shapes and check for collisions etc. Also sound, buttons, a basic scene system and some basic math stuff is there. Physics engine is still completely missing. Also the documentation is quite lacking

---

## Note to Windows users
I have **tried** to get this thing running under windows, but it hasn't gone as planned. I haven't used Windows for a few years as my desktop OS, so I have no clue how to make stuff compatible between GNU/Linux and Windows.

### What have I *tried* so far
- **Cygwin** in a vm (it was borked in wine). It was slow af and SDL libraries failed to compile in it for some reason. The binaries provided by Cygwin were too old and didn't work for this project
- **Visual Studio**. Opened it, closed it. Didn't know how to use that monster
- **MinGW**
	- **On windows**: Gave up, CMD sucks and should be illegal to ship with an operating system
	- **On GNU/Linux**: Ehh... g++.exe ran fine under wine, but there were a ton of incompatibilities between GNU/Linux and Windows libraries making it not compile. Mostly filesystem and timer specific issues. There were probably a bit more issues as well, but I couldn't really spot them when there was about 10 wine fixmes for each g++ error.

### What does this mean?
No Windows support. Here's an alternative operating system for you: https://archlinux.org/download/
