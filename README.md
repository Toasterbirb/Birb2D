# Birb2D
Birb2D is a simplistic 2D game engine made by an amateur programmer, with the goal to learn how game engines and development is done in more depth and from a complete behind the scenes perspective.

Documentation coming soon(tm).

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
	- [ ] Buttons
	- [x] Text
	- [ ] Dropdown menu
	- [ ] Slider
	- [ ] Input box
	- [x] Resizable UI
		- [ ] Resolution independent UI scaling
		- [ ] Anchors
- [x] Sound
- [ ] Animation
- [ ] Physics
- [ ] To be continued...
