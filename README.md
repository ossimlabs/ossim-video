# ossim-video
Contains C++ library code for visualizing and processing video.

## Build Instructions 
This repository is built as part of the OSSIM suite of repositories, using the centralized CMake build system in [ossimlabs/ossim](http://github.com/ossimlabs/ossim). See the build instructions in [ossim/README.md](http://github.com/ossimlabs/ossim/blob/master/README.md). As long as this repository is located in the same parent directory as [OSSIM](http://github.com/ossimlabs/ossim), CMake will detect it and create the Makefiles in `<build-dir>/<build-type>/ossim-video`. You can `cd` into that directory and type `make` if you only want to build ossim-video.

