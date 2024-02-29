#!/bin/bash

PLATFORM=$1

# exit codes:
# 1: unsupported platform
# 3: configuration failed
# 4: build failed

cmake -B $RUNNER_WORKSPACE/build -DCMAKE_BUILD_TYPE=Release -DSCRATCHCPP_PLAYER_BUILD_UNIT_TESTS=OFF || exit 3

if [[ "$PLATFORM" == "win32" ]]; then
	cmake --build $RUNNER_WORKSPACE/build -j4 || exit 4
elif [[ "$PLATFORM" == "win64" ]]; then
	cmake --build $RUNNER_WORKSPACE/build -j4 || exit 4
elif [[ "$PLATFORM" == "macos" ]]; then
	cmake --build $RUNNER_WORKSPACE/build -j6 || exit 4
else
	cmake --build $RUNNER_WORKSPACE/build -j$(nproc --all) || exit 4
fi
