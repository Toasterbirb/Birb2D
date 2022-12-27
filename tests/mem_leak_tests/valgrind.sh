#!/bin/sh
VALGRIND_FLAGS="--track-origins=yes --show-leak-kinds=all --leak-check=full"
ls | xargs -n1 file | awk '/ELF/ {print $1}' | tr -d ':' | fzf --height=10 | xargs -i valgrind ${VALGRIND_FLAGS} ./{}
