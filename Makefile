OS := $(shell uname)
ARCH := $(shell uname -m)

.PHONY: all clean


ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY ?= $(LEAP_SDK)/lib/x64/libLeap.so -Wl,-rpath,$(LEAP_SDK)/lib/x64
  else
    LEAP_LIBRARY ?= $(LEAP_SDK)/lib/x86/libLeap.so -Wl,-rpath,$(LEAP_SDK)/lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY ?= $(LEAP_SDK)/lib/libLeap.dylib
endif

CPPFLAGS=-I$(LEAP_SDK)/include
CXXFLAGS=-Wall -g -std=c++11
SOURCES=Sample.cpp PrototypeListener.cpp
HEADERS=PrototypeListener.h
OBJ=Sample.o PrototypeListener.o
EXECUTABLE=Sample

Sample: $(OBJ)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(EXECUTABLE) $(LEAP_LIBRARY)

Sample.o : Sample.cpp

PrototypeListener.o : PrototypeListener.cpp Sample.cpp

recompress :
	gzip -r gestures

decompress :
	gunzip -r gestures

clean:
	rm -rf Sample $(OBJ)


