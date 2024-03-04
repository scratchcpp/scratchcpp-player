#!/bin/bash

### This script generates an installer and a Qt Installer Framework repository and uploads it
git config --global user.name "GitHub Actions Bot"
git config --global user.email "<>"

REPO="$1"
part1='/<Version>/c\\t<Version>'
VERSION=${previous_tag//v}
part2='<\/Version>'
part3='/<ReleaseDate>/c\\t<ReleaseDate>'
part4='<\/ReleaseDate>'
sed -i -e "${part1}${VERSION}${part2}" release/win_installer/config/config.xml
sed -i -e "${part1}${VERSION}${part2}" release/win_installer/packages/${windows_app_name}/meta/package.xml
sed -i -e "${part3}$(date +'%Y-%m-%d')${part4}" release/win_installer/packages/${windows_app_name}/meta/package.xml

mv win_release/* "release/win_installer/packages/${windows_app_name}/data/${app_name}"
cd release/win_installer
curl -L https://aka.ms/vs/16/release/VC_redist.x64.exe > packages/com.microsoft.vcredist/data/VC_redist.x64.exe || exit $?
./build.sh $(echo ../../../Tools/QtInstallerFramework/*/bin/binarycreator.exe) || exit $?
mv *installer.exe ../..

if (( $update_windows_repository == 1 )); then
	./update_repo.sh $(echo ../../../Tools/QtInstallerFramework/*/bin/repogen.exe) || exit $?
	old_dir="$(pwd)"
	cd "$REPO"
	git checkout -b tmp
	git branch -D master &&
	git switch --orphan master &&
	mv $old_dir/repository/* ./ &&
	rm -rf "$old_dir/repository" &&
	git add -A &&
	git commit -m "Generate repository" || exit $?
	git push -f --set-upstream origin master
fi
