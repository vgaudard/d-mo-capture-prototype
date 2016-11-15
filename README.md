# D-MO capture prototype

This project is part of a study project in the computer science departement of
INSA Rennes.

Its goal is to learn how to capture Leap Motion data, as well as recording data
about gestures made by different subjects. This data will later be used to
recognize gestures made by a user.

## Data

Data about gestures is stored in `gestures/[gesture_name]/[subject_name]/`.
These folders contain several compressed XML files containing the different
recordings.

Some editors automatically decompress `gzip` files. If need be, use `make
decompress`.

## Compiling

To compile this project, you must specify where the Leap SDK is installed. (e.g. `make LEAP_SDK=~/lib/LeapSdk/`)

`MetadataEntry` needs qt4. More details about it will be added later. (see `make` and `qmake`)
