#!/bin/bash

set -e

APP_NAME=cardputer-prog-desktop
SRC_PATH=desktop
BUILD_PATH=build/desktop

mkdir -p "$BUILD_PATH"

cmake -B "$BUILD_PATH" -S "$SRC_PATH" \
    -DAPP_NAME=$APP_NAME \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD_PATH"

echo "Built: $BUILD_PATH/$APP_NAME"
