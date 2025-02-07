#!/bin/bash

.ci/common/build.sh macos || exit $?
mv $(find . -name "${executable_name}.app") . || exit $?

mkdir -p "${executable_name}.app/Contents/Frameworks"

for file in $(find . -type f -name "*.dylib"); do
    install_name_tool -change "$file" "@rpath/$file" "${executable_name}.app/Contents/MacOS/${executable_name}" || exit $?
    cp "$file" "${executable_name}.app/Contents/Frameworks/"
done

macdeployqt "${executable_name}.app" -qmldir=src || exit $?

# Sign using self-signed certificate
codesign --verify --verbose --force --deep -s - "${executable_name}.app"
codesign --verify --verbose "${executable_name}.app"

# Create .dmg with an install screen
npm install -g appdmg || exit $?
mv ${executable_name}.app res/macos-release/
dmg_name=`echo "${app_name}.dmg" | tr ' ' '_'`
appdmg res/macos-release/scratchcpp-player.json "$dmg_name" || exit $?

# Verify
#spctl -a -t open --context context:primary-signature -v "$dmg_name"
