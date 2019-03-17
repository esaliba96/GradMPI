#!/bin/sh
grep -n npb "$2" > time
mkdir -p "$1"
java reader 0 > "$1"/"$4"x.32."$3"
java reader 1 > "$1"/"$4"x.64."$3"
java reader 2 > "$1"/"$4"x.128."$3"
