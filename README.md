# sdl-game
## Features
* More later

## Dependencies
1. SDL2
2. SDL2_image
3. SDL2_ttf
4. Boost
5. nlohmann json ([Website](https://nlohmann.github.io/json/))

## Building
### Requirements
1. Meson Build System ([Website](http://mesonbuild.com/))
2. Ninja ([Website](https://ninja-build.org))
3. Dependencies Listed Above

### Steps
1. `mkdir build`
2. `meson build` (for clang: add `CC=clang CXX=clang++` in front)
3. `cd build`
4. `ninja`
