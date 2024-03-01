#!/bin/bash

BUILD_DIR=$1
PLATFORM=$2

# exit codes:
# 1: unsupported platform
# 3: configuration failed
# 4: build failed

mkdir -p "$BUILD_DIR"

if [[ "$PLATFORM" == "win64" ]] || [[ "$PLATFORM" == "win32" ]]; then
	cmake -B "$BUILD_DIR" -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DSCRATCHCPP_PLAYER_BUILD_UNIT_TESTS=OFF || exit 3
else
	cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release -DSCRATCHCPP_PLAYER_BUILD_UNIT_TESTS=OFF || exit 3
fi

if [[ "$PLATFORM" == "win32" ]]; then
	cmake --build "$BUILD_DIR" -j4 || exit 4
elif [[ "$PLATFORM" == "win64" ]]; then
	cmake --build "$BUILD_DIR" -j4 || exit 4
elif [[ "$PLATFORM" == "macos" ]]; then
	cmake --build "$BUILD_DIR" -j6 || exit 4
else
	cmake --build "$BUILD_DIR" -j$(nproc --all) || exit 4
fi
