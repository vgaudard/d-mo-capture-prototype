#pragma once
#include <iostream>
#include <cstring>

#include "Leap.h"

namespace DMO_Prototype
{
    class PrototypeListener : public Leap::Listener
    {
        public:
            PrototypeListener(std::ostream& stream);
            virtual ~PrototypeListener();
            virtual void onInit(const Leap::Controller&);
            virtual void onConnect(const Leap::Controller&);
            virtual void onDisconnect(const Leap::Controller&);
            virtual void onExit(const Leap::Controller&);
            virtual void onFrame(const Leap::Controller&);
            virtual void onFocusGained(const Leap::Controller&);
            virtual void onFocusLost(const Leap::Controller&);
            virtual void onDeviceChange(const Leap::Controller&);
            virtual void onServiceConnect(const Leap::Controller&);
            virtual void onServiceDisconnect(const Leap::Controller&);

        private:
            virtual void onFrame_Hands(const Leap::Controller&, const Leap::Frame& frame);
            virtual void onFrame_Fingers(const Leap::Controller&, const Leap::Frame& frame, const Leap::Hand& hand);
            virtual void onFrame_Arm(const Leap::Controller&, const Leap::Frame& frame, const Leap::Hand& hand);
            virtual void onFrame_Tools(const Leap::Controller&, const Leap::Frame& frame);
            virtual void onFrame_Gestures(const Leap::Controller&, const Leap::Frame& frame);
            virtual void onFrame_CircleGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture);
            virtual void onFrame_SwipeGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture);
            virtual void onFrame_KeyTapGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture);
            virtual void onFrame_ScreenTapGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture);

            std::ostream& outStream;

            static const std::string fingerNames[5];
            static const std::string boneNames[4];
            static const std::string stateNames[4];
    };
}
