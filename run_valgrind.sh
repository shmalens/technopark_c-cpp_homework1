#!/usr/bin/env bash

valgrind -s --tool=memcheck --leak-check=full --track-origins=yes  --show-leak-kinds=all ./build/compilation