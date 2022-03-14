#!/usr/bin/env bash

make

cd 42-cluster || exit
make && make bot

./cluster ../clusterbot ./bot

cd - || exit
