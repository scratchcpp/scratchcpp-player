#!/bin/bash

sudo apt update
case "$1" in
    aarch64)
        sudo apt install -y g++-aarch64-linux-gnu
        ;;
esac
