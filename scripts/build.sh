#!/bin/bash
rm -rf build && mkdir build && cd build
cmake -S ..  -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build . --parallel 4
