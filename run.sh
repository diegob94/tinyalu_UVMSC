#!/bin/bash

set -v -e

SCRIPT_DIR=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
pushd $SCRIPT_DIR

test -d work || mkdir work
test -d work/sim_build || mkdir work/sim_build

pushd work

cmake -GNinja -S ../scripts -B ./sim_build |& tee sim_compile.log
cmake --build ./sim_build |& tee -a sim_compile.log
./sim_build/sim +trace |& tee sim_run.log
