#include <iostream>
#include <cstring>

#include "Leap.h"

#include "PrototypeListener.h"

using namespace DMO_Prototype;

int main(int argc, char** argv)
{
    PrototypeListener listener;
    Leap::Controller controller;

    std::cout << "<recording>" << std::endl;

    controller.addListener(listener);
    std::cin.get(); // Press enter to end recording
    controller.removeListener(listener);

    std::cout << "</recording>" << std::endl;

    return 0;
}


