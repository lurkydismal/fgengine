#!/bin/bash
export SCRIPT_DIRECTORY=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export BUILD_DIRECTORY="$SCRIPT_DIRECTORY/out"

clear

source ./config.sh && {

mkdir -p "$BUILD_DIRECTORY"

for partToBuild in "${partsToBuild[@]}"; do

    source "$partToBuild/config.sh" && './build_general.sh' "$partToBuild"

    if [ $? -ne 0 ]; then
        break
    fi

done

}
