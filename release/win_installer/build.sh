#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BINARYCREATOR=$1
source "$SCRIPT_DIR/env.sh"

if [[ "$BINARYCREATOR" == "" ]]; then
	if [[ `command -v binarycreator` != "" ]]; then
		BINARYCREATOR=binarycreator
	else
		echo "No binarycreator executable path specified!"
		exit 1
	fi
fi

echo "D: binarycreator: $BINARYCREATOR"
echo "Creating installer binary..."
$BINARYCREATOR --offline-only -c config/config.xml -p packages "$FILE_NAME" || exit $?
