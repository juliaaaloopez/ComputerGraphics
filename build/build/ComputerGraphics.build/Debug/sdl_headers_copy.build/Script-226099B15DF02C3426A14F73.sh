#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2
  /usr/local/Cellar/cmake/3.28.1/bin/cmake -E copy_if_different /Users/julialopezpinot/Desktop/ComputerGraphics/libraries/sdl2/include/close_code.h /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2/include/close_code.h
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2
  /usr/local/Cellar/cmake/3.28.1/bin/cmake -E copy_if_different /Users/julialopezpinot/Desktop/ComputerGraphics/libraries/sdl2/include/close_code.h /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2/include/close_code.h
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2
  /usr/local/Cellar/cmake/3.28.1/bin/cmake -E copy_if_different /Users/julialopezpinot/Desktop/ComputerGraphics/libraries/sdl2/include/close_code.h /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2/include/close_code.h
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2
  /usr/local/Cellar/cmake/3.28.1/bin/cmake -E copy_if_different /Users/julialopezpinot/Desktop/ComputerGraphics/libraries/sdl2/include/close_code.h /Users/julialopezpinot/Desktop/ComputerGraphics/build/libraries/sdl2/include/close_code.h
fi
