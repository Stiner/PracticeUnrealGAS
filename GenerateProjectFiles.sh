#!/bin/bash

PATH_TO_ENGINE=$HOME/Epic\ Games/UE_5.1

sh "$PATH_TO_ENGINE/Engine/Build/Batchfiles/Mac/GenerateProjectFiles.sh" \
 -project="$(ls $(dirname $(realpath $0))/*.uproject)" \
