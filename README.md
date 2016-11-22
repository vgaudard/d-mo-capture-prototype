# D-MO capture prototype

This project is part of a study project in the computer science departement
of INSA Rennes.

Its goal is to learn how to capture Leap Motion data, as well as recording
data about gestures made by different subjects. This data will later be used
to recognize gestures made by a user.

## Data

Data about gestures is stored in `gestures/[gesture_name]/[subject_name]/`.
These folders contain several XML files containing the different recordings.

For convenience, you can compress it with `make compressGestures`, and then
decompress it using `make decompressGestures`.

## Dependencies

You need to install the [Leap Motion sdk](https://developer.leapmotion.com/v2).

You also need the following package: `qt-sdk`

On Ubuntu, use the following command:

```
sudo apt-get install qt-sdk
```

## Compiling

To compile this project, you must specify where the Leap SDK is installed. (e.g.
`make LEAP_SDK=~/lib/LeapSdk/`) after creating the makefile.

While in the `MetadataEntry` folder execute the following commands, replacing
`[LEAP_SDK]` with the path to the SDK (The folder that contains `include` and
`lib`).

```
qmake LEAP_SDK=[LEAP_SDK]
make LEAP_SDK=[LEAP_SDK]
```

You can then execute the metadata and gestures collector with `./MetadataEntry`.

## Library explanations

As this project will be worked on by people that might not know how to use Qt or
the Leap SDK, here are some brief explanations.

### Qt

#### Editing and compiling

For ease of use, prefer Qt Creator.

#### Classes and files

Most Qt Objects used to display a UI element inherit from `QWidget` or a
subclass.

Custom Qt widgets are created using three files: `[class].cpp`, `[class].h`, and
`[class].ui`.

The `.cpp` and `.h` file are usual, but need a few elements. The `.ui` file
contains the window details. Use Qt Creator or Qt Designer to edit it.

#### Signals and slots

Events in Qt are managed with signals and slots. (A class using signals and
slots must contain the macro `Q_OBJECT`.) In this project, only Qt signals are
used, and some slots are added.

*Signals* are sent when the user interacts with the user interface (e.g. when
user clicks on a button, the signal `clicked()` of this button is sent (note the
brackets)).

*Slots* are functions that can be executed when a signal is sent.

Signals and slots are then connected using `QObject::connect` (see below) so
that, when the signal is sent, every connected slot is executed.

To connect a signal and a slot, use

```
QObject::connect(objectContainingTheSignal, SIGNAL(signalName(parameterType)),
                 objectContainingTheSlot,   SLOT(slotName(parameterType)));
```

### Leap Motion SDK

To get Leap Motion data, you need to create a controller (`Leap::Controller`),
as well as a listener (object inheriting `Leap::Listener`).

The listener has functions called on several events.

`onFrame` is called every frame the Leap Motion can detect, with appropriate
data. Check `PrototypeListener::onFrame` to see how to extract needed data.
