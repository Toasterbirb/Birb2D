# Birb2D
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
### Generate documentation
```sh
doxygen doxygen_config
```

### Shared library
```sh
make -j$(nproc) engine_lib
```

### Pong
```sh
make -j$(nproc) pong
```

### Run tests
```sh
make -j$(nproc) run_tests
```

### Installation
Simply compile the shared library and copy the headerfiles with
```sh
make -j$(nproc) install
```
to uninstall, run the following
```sh
make uninstall
```

## Roadmap
- [x] Sprite rendering
- [x] Timestep
- [x] Basic input handling (currently at cave man stage)
- [x] Entity system (Partially functional currently)
- [ ] Basic UI functionality
	- [x] Buttons
	- [x] Text
	- [ ] Dropdown menu
	- [ ] Slider
	- [ ] Input box
	- [x] Resizable UI
		- [ ] Resolution independent UI scaling
		- [ ] Anchors
- [x] Sound
- [x] Animation (sprite based animations supported)
- [ ] Physics
- [ ] To be continued...
