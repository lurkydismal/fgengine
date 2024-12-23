#!/bin/bash
export SCRIPT_DIRECTORY=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export BUILD_DIRECTORY_NAME='out'
export BUILD_DIRECTORY="$SCRIPT_DIRECTORY/$BUILD_DIRECTORY_NAME"
export LINK_FLAGS="-lSDL3 -s -O1 -static-libgcc"
export LINKER="ccache gcc"
export EXECUTABLE_NAME="main.out"

clear

source './config.sh' && {

mkdir -p "$BUILD_DIRECTORY"

for partToBuild in "${partsToBuild[@]}"; do

    source "$partToBuild/config.sh" && './build_general.sh' "$partToBuild"

    if [ $? -ne 0 ]; then
        break
    fi

done

clear

$LINKER $LINK_FLAGS $BUILD_DIRECTORY/lib* -o $BUILD_DIRECTORY/$EXECUTABLE_NAME

}
