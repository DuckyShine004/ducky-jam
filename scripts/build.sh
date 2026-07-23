#!/bin/bash

declare -A preset_set

preset_set[release]=1
preset_set[debug]=1
preset_set[profile]=1

set -e

PRESET="${1:-release}"

if [[ -z ${preset_set[$PRESET]} ]]; then
    echo "ERROR: usage is ./scripts/build.sh <preset> (default: release, debug, profile)"
    exit 1
fi

mkdir -p "build/${PRESET}"

echo "INFO: Building '${PRESET}'"

cmake --preset "${PRESET}"
cmake --build "build/${PRESET}"

echo "INFO: Running '${PRESET}'"

if [[ $PRESET == "release" ]]; then
    ./build/release/ducky-jam
elif [[ $PRESET == "debug" ]]; then
    ./build/debug/ducky-jam
elif [[ $PRESET == "profile" ]]; then
    perf record --latency -g -F 999 ./build/profile/ducky-jam
    perf report --latency
fi

rm -rf .cache/logs/*
