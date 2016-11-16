#include <iostream>
#include <cstring>

#include "Leap.h"

#include "PrototypeListener.h"

using namespace DMO_Prototype;

int main(int argc, char** argv)
{
    PrototypeListener listener(std::cout);
    Leap::Controller controller;

    controller.addListener(listener);
    std::cin.get(); // Press enter to end recording
    controller.removeListener(listener);

    return 0;
}


