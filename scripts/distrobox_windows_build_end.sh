#!/bin/sh

# This oneliner creates a distrobox environment that you can use
# for building birb2d projects for windows. The create_release.sh
# script can use this distrobox environment if needed

distrobox create --image ubuntu --name birb2d_win_build_env --pre-init-hooks "apt-get update && apt-get -yq install git gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 cmake make"
