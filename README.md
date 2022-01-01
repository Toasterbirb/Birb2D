# Birb2D
Birb2D is a simplistic 2D game engine made by an amateur programmer, with the goal to learn how game engines and development is done in more depth and from a complete behind the scenes perspective.

Documentation coming soon(tm).

## Games made with Birb2D
- [Flappy Birb](https://github.com/Toasterbirb/Flappy-Birb)

## External libraries
- SDL2
- doctest (included as a headerfile)

## Building
### Using CMake
```sh
mkdir build
cd build
cmake ..
make -j4
```

### Using make (might be going away at some point)
#### Editor
```sh
make -j4 editor
```

#### Ping Pong
```sh
make -j4 ping-pong
```

#### Run tests
```sh
make -j4 test
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
