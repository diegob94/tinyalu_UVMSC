#!/bin/bash

cat ./compile_commands.json | grep -F '"command":' | awk -v FS='"' '{print $4}' | sed 's/cpp.o/cpp.i -E/' | cat <(echo set -v) /dev/stdin | bash


