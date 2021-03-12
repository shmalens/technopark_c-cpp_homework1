#!/usr/bin/env bash

cppcheck --inconclusive --enable=all --language=c project
cppcheck --inconclusive --enable=all --language=c++ test