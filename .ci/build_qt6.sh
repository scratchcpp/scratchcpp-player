#!/bin/bash

sudo apt install -y lsb-release

qt_version="$1"

if [[ "$2" == "" ]]; then
    qt_modules=""
else
    qt_modules=",$(echo $2 | tr ' ' ',')"
fi

target_arch="$3"
root_path="$(pwd)"
#host_prefix="${root_path}/qt-host"
host_prefix="$QT_HOST_PATH"
cross_prefix="$QT_CROSS_PATH"
target_prefix="/usr/local/qt"

echo "Qt version to build: ${qt_version}"
echo "Qt modules: ${qt_modules}"
echo "Target architecture: ${target_arch} (${BUILD_ARCH_NAME})"

# Clone Qt
git clone https://github.com/qt/qt5 qt || exit 1
cd qt
git checkout $(git tag | grep '^v6\.8\.[0-9]*$' | sort -V | tail -n 1) || exit 1
./init-repository --module-subset=qtbase,qttools,qtdeclarative,qtsvg${qt_modules} || exit 1

# Build Qt (host)
#mkdir host-build
#cd host-build
#echo "Building host Qt..."
#../configure -release -nomake examples -nomake tests -opensource -confirm-license -prefix "$host_prefix" || exit 1
#cmake --build . --parallel $(nproc --all) || exit 1
#echo "Installing host Qt..."
#cmake --install . || exit 1
#cd ..
#rm -rf host-build

# Build Qt (cross)
mkdir cross-build
cd cross-build
echo "Cross-compiling Qt..."
../configure -release -opengl desktop -nomake examples -nomake tests -qt-host-path "$host_prefix" -xplatform "$BUILD_PLATFORM" \
             -device-option CROSS_COMPILE="$BUILD_TOOLCHAIN_PREFIX" -sysroot "$BUILD_SYSROOT_PATH" -opensource -confirm-license \
             -prefix "$target_prefix" -extprefix "$cross_prefix" -- -DCMAKE_TOOLCHAIN_FILE="$BUILD_TOOLCHAIN_CONFIG" \
             -DQT_FEATURE_xcb=ON -DFEATURE_xcb_xlib=ON -DQT_FEATURE_xlib=ON || exit 1
cmake --build . --parallel $(nproc --all) || exit 1
echo "Installing cross-compiled Qt..."
cmake --install . || exit 1
cd ..

# Cleanup
cd ..
rm -rf qt
# Required for cache
sudo chmod 777 -R ${BUILD_SYSROOT_PATH}
