#!/usr/bin/env bash

echo "starting multicam..."
./bin/multicam &
sleep 10
echo "removing window decorations..."
./remove_decorations.py
echo "done."

