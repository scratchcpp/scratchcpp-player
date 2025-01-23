#!/bin/bash

sudo apt install -y lsb-release

target_arch="$1"
root_path="$(pwd)"
sysroot_path="${root_path}/sysroot"
sysroot_ubuntu_version="$(lsb_release -rs).1"
sysroot_ubuntu_codename="$(lsb_release -cs)"
cross_prefix="${root_path}/qt-cross"
toolchain_config="${root_path}/.ci/qt6-toolchain.cmake"

case "$target_arch" in
    aarch64)
        target_arch_name="armv8-a"
        target_arch_debian_name="arm64"
        toolchain_name="aarch64-linux-gnu"
        target_platform="linux-aarch64-gnu-g++"
        ;;
esac

toolchain_prefix="${toolchain_name}-"

echo "Target architecture: ${target_arch} (${target_arch_name})"

# Install dependencies
${root_path}/.ci/install_cross_compiler.sh "${target_arch}" || exit 1
sudo apt install -y qemu-user-static || exit 1

# Prepare sysroot
echo "Preparing sysroot..."
curl "https://cdimage.ubuntu.com/ubuntu-base/releases/${sysroot_ubuntu_codename}/release/ubuntu-base-${sysroot_ubuntu_version}-base-${target_arch_debian_name}.tar.gz" > ./ubuntu-base.tar.gz || exit 1
mkdir -p "$sysroot_path"
sudo tar -xvzf ubuntu-base.tar.gz -C "$sysroot_path" || exit 1
rm ubuntu-base.tar.gz
sudo update-binfmts --enable qemu-arm || exit 1
sudo mount -o bind /dev "${sysroot_path}/dev" || exit 1
sudo cp /etc/resolv.conf "${sysroot_path}/etc" || exit 1
sudo chmod 1777 "${sysroot_path}/tmp" || exit 1
sudo cp "${root_path}/.ci/qt6_deps.sh" "${sysroot_path}/"
sudo chroot "$sysroot_path" /bin/bash -c "/qt6_deps.sh" || exit 1
sudo chroot "$sysroot_path" /bin/bash -c "apt update && apt install -y symlinks libssl-dev && symlinks -rc /" || exit 1
sudo umount "${sysroot_path}/dev" || exit 1

# Prepare environment
echo "BUILD_SYSROOT_PATH=$sysroot_path" >> "$GITHUB_ENV"
echo "BUILD_TOOLCHAIN_NAME=$toolchain_name" >> "$GITHUB_ENV"
echo "BUILD_TOOLCHAIN_PREFIX=$toolchain_prefix" >> "$GITHUB_ENV"
echo "BUILD_TOOLCHAIN_CONFIG=$toolchain_config" >> "$GITHUB_ENV"
echo "BUILD_ARCH_NAME=$target_arch_name" >> "$GITHUB_ENV"
echo "BUILD_PLATFORM=$target_platform" >> "$GITHUB_ENV"
echo "QT_ROOT_DIR=$cross_prefix" >> "$GITHUB_ENV"
