#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
REPOGEN=$1
source "$SCRIPT_DIR/env.sh"

if [[ "$REPOGEN" == "" ]]; then
	if [[ `command -v repogen` != "" ]]; then
		REPOGEN=repogen
	else
		echo "No repogen executable path specified!"
		exit 1
	fi
fi

echo "D: repogen: $REPOGEN"
echo "Generating repository..."
$REPOGEN -p packages repository || exit $?
