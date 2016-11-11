#!/bin/bash

if [[ "$#" -ne 3 ]]; then
    echo "Usage: `basename $0` gesture_name subject_name try"
    echo "Example: `basename $0` swipe_right_to_left bob 2"
    exit 1
fi
gesture_name="$1"
subject_name="$2"
try="$3"

tmp=$(mktemp)
folder="gestures/$gesture_name/$subject_name"
path="$folder/$try"".xml.gz"

mkdir -p "$folder"
echo "Recording..."
echo "Press Return when done"
./Sample > "$tmp"
gzip < "$tmp" > "$path"
rm "$tmp"
echo "Saved and compressed to $path"
