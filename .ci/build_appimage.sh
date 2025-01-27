#!/bin/bash

sudo ()
{
    [[ $EUID = 0 ]] || set -- command sudo "$@"
    "$@"
}

# Build
if [[ "$1" == "" ]]; then
    PLATFORM=linux
else
    PLATFORM="linux_$1"
fi
.ci/common/build.sh appimage_build $PLATFORM || exit 1

repo_dir=$(pwd)
cd appimage_build

# Build linuxdeploy
sudo apt install -y build-essential g++ pkg-config curl wget libpng-dev libjpeg-dev zsync desktop-file-utils libxcb-cursor0 &&
git clone https://github.com/Open-Typer/linuxdeploy linuxdeploy-build --recurse-submodules &&
mkdir linuxdeploy-build/build
cd linuxdeploy-build/build &&
# Add src/core/copyright to include paths (see https://github.com/linuxdeploy/linuxdeploy/issues/212)
cmake -DCMAKE_CXX_FLAGS=-isystem\ $(pwd)/../src/core/copyright .. &&
make -j$(nproc --all) &&
mv bin/linuxdeploy ../.. &&
cd ../.. &&
rm -rf linuxdeploy-build &&

# Build linuxdeploy-plugin-qt
sudo apt install -y nlohmann-json3-dev &&
git clone https://github.com/Open-Typer/linuxdeploy-plugin-qt plugin-qt --recurse-submodules &&
mkdir plugin-qt/build &&
cd plugin-qt/build &&
cmake .. &&
make -j$(nproc --all) &&
mv bin/linuxdeploy-plugin-qt ../.. &&
cd ../.. &&
rm -rf plugin-qt &&

# Build linuxdeploy-plugin-appimage
git clone https://github.com/linuxdeploy/linuxdeploy-plugin-appimage plugin-appimage --recurse-submodules &&
mkdir plugin-appimage/build &&
cd plugin-appimage/build &&
cmake .. &&
make -j$(nproc --all) &&
mv src/linuxdeploy-plugin-appimage ../.. &&
cd ../.. &&
rm -rf plugin-appimage

# Download appimagetool
wget https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage &&
mv appimagetool-*.AppImage appimagetool
chmod +x appimagetool
export PATH=$(pwd):$PATH

# Install patchelf from PyPI (see https://github.com/linuxdeploy/linuxdeploy-plugin-qt/issues/133#issuecomment-1608168363)
sudo apt install -y python3-pip
python3 -m venv .venv
source .venv/bin/activate
pip3 install patchelf
patchelf --version

# Use custom ldd and strip
if [[ "$PLATFORM" == "linux_aarch64" ]]; then
    ln -s /usr/bin/${BUILD_TOOLCHAIN_PREFIX}strip strip
    sudo cp ../.ci/bin/xldd /usr/bin/${BUILD_TOOLCHAIN_PREFIX}ldd
    ln -s /usr/bin/${BUILD_TOOLCHAIN_PREFIX}ldd ldd
    export CT_XLDD_ROOT="$BUILD_SYSROOT_PATH"
fi

# Set LD_LIBRARY_PATH (directories with *.so files)
# TODO: Installing with cmake is probably a better idea
LD_LIBRARY_PATH=""

for file in $(find . -type f -name "*.so*"); do
    dir=$(dirname "$file")
    if [[ ":$LD_LIBRARY_PATH:" != *":$dir:"* ]]; then
        LD_LIBRARY_PATH="$LD_LIBRARY_PATH:`readlink -f $dir`"
    fi
done

LD_LIBRARY_PATH=${LD_LIBRARY_PATH#:}
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QT_ROOT_DIR/lib" # Qt
export LD_LIBRARY_PATH
echo "LD_LIBRARY_PATH set to: $LD_LIBRARY_PATH"

# Build AppImage
if [[ "$PLATFORM" == "linux_aarch64" ]]; then
    wget https://github.com/AppImage/type2-runtime/releases/download/continuous/runtime-aarch64
    export ARCH=arm_aarch64
    APPIMAGE_ARCH=aarch64
    export LDAI_RUNTIME_FILE=runtime-aarch64
    export QEMU_LD_PREFIX="$BUILD_SYSROOT_PATH"
    export PATH="$QT_ROOT_DIR/bin:$PATH" # use cross Qt
    export PATH="$PATH:$QT_HOST_PATH/libexec"
else
    APPIMAGE_ARCH=x86_64
fi

export QML_SOURCES_PATHS=$(pwd)/src &&
export EXTRA_QT_MODULES="qml;svg;" &&
export LDAI_UPDATE_INFORMATION="${appimage_zsync_prefix}${app_name}*-${APPIMAGE_ARCH}.AppImage.zsync"
echo "AppImage update information: ${LDAI_UPDATE_INFORMATION}"

./linuxdeploy --appdir AppDir -e src/app/${executable_name} -i $repo_dir/res/${executable_name}.png -d $repo_dir/release/appimage.desktop --plugin qt --output appimage

mv *.AppImage* $repo_dir
