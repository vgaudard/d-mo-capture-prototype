#include <iostream>
#include <cstring>

#include "Leap.h"

#include "PrototypeListener.h"

using namespace DMO_Prototype;

// The following static arrays allow the translation number => name
const std::string PrototypeListener::fingerNames[] = {"thumb", "index", "middle", "ring", "pinky"};
const std::string PrototypeListener::boneNames[] = {"metacarpal", "proximal", "middle", "distal"};
const std::string PrototypeListener::stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

PrototypeListener::PrototypeListener(std::ostream & stream) :
    outStream(&stream)
{
}

PrototypeListener::~PrototypeListener()
{
}

void PrototypeListener::startRecording()
{
    *outStream << "<recording>" << std::endl;
}

void PrototypeListener::onInit(const Leap::Controller& controller)
{
}

void PrototypeListener::onConnect(const Leap::Controller& controller)
{
    controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void PrototypeListener::onDisconnect(const Leap::Controller& controller)
{
    // Note: not dispatched when running in a debugger.
}

void PrototypeListener::onExit(const Leap::Controller& controller)
{
    *outStream << "</recording>" << std::endl;
}

void PrototypeListener::onFrame(const Leap::Controller& controller)
{
    const Leap::Frame frame = controller.frame();
    if (frame.hands().count() == 0)
        return;

    *outStream << std::string(2, ' ')   << "<instant "
              << "id=\""               << frame.id()                         << "\" "
              << "timestamp=\""        << frame.timestamp()                  << "\" "
              << "hands=\""            << frame.hands().count()              << "\" "
              << "extended_fingers=\"" << frame.fingers().extended().count() << "\" "
              << "tools=\""            << frame.tools().count()              << "\" "
              << "gestures=\""         << frame.gestures().count()           << "\" "
              << ">"                   << std::endl;

    onFrame_Hands(controller, frame);
    onFrame_Tools(controller, frame);
    onFrame_Gestures(controller, frame);

    *outStream    << std::string(2, ' ')   << "</instant>" << std::endl;

}

void PrototypeListener::onFocusGained(const Leap::Controller& controller)
{
}

void PrototypeListener::onFocusLost(const Leap::Controller& controller)
{
}

void PrototypeListener::onDeviceChange(const Leap::Controller& controller)
{
}

void PrototypeListener::onServiceConnect(const Leap::Controller& controller)
{
}

void PrototypeListener::onServiceDisconnect(const Leap::Controller& controller)
{
}

void PrototypeListener::setStream(std::ostream* stream)
{
    outStream = stream;
}

void PrototypeListener::onFrame_Hands(const Leap::Controller& controller, const Leap::Frame& frame)
{
    Leap::HandList hands = frame.hands();
    *outStream << std::string(4, ' ') << "<hands>" << std::endl;
    for (auto hl = hands.begin(); hl != hands.end(); ++hl)
    {
        const Leap::Hand hand = *hl;
        const Leap::Vector normal = hand.palmNormal();
        const Leap::Vector direction = hand.direction();
        *outStream    << std::string(6, ' ') << "<hand "
            << "type=\""           << (hand.isLeft() ? "left" : "right") << "\" "
            << "id=\""             << hand.id()                          << "\" "
            << "palmPosition=\""   << hand.palmPosition()                << "\" "
            << ">"                 << std::endl;

        *outStream   << std::string(8, ' ') << "<orientation "
            << "pitch=\""          << direction.pitch() * Leap::RAD_TO_DEG << "\" "
            << "roll=\""           << normal.roll() * Leap::RAD_TO_DEG     << "\" "
            << "yaw=\""            << direction.yaw() * Leap::RAD_TO_DEG   << "\" "
            << "/>"                << std::endl;

        onFrame_Fingers(controller, frame, hand);
        onFrame_Arm(controller, frame, hand);

        *outStream << std::string(6, ' ') << "</hand>"    << std::endl;
    }
    *outStream << std::string(4, ' ') << "</hands>" << std::endl;
}

void PrototypeListener::onFrame_Fingers(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Hand& hand)
{
    const Leap::FingerList fingers = hand.fingers();
    *outStream << std::string(8, ' ') << "<fingers>" << std::endl;
    for (auto fl = fingers.begin(); fl != fingers.end(); ++fl)
    {
        const Leap::Finger finger = *fl;
        *outStream  << std::string(10, ' ') << "<finger "
            << "type=\""           << fingerNames[finger.type()] << "\" "
            << "id=\""             << finger.id()                << "\" "
            << "length=\""         << finger.length()            << "\" "
            << "width=\""          << finger.width()             << "\" "
            << ">"                 << std::endl;

        // Get finger bones
        *outStream  << std::string(10, ' ') << "<bones>" << std::endl;
        for (int b = 0; b < 4; ++b)
        {
            Leap::Bone::Type boneType = static_cast<Leap::Bone::Type>(b);
            Leap::Bone bone = finger.bone(boneType);
            *outStream   << std::string(12, ' ') << "<bone "
                << "type=\""            << boneNames[boneType] << "\" "
                << "start=\""           << bone.prevJoint()    << "\" "
                << "end=\""             << bone.nextJoint()    << "\" "
                << "direction=\""       << bone.direction()    << "\" "
                << "/>"                 << std::endl;
        }
        *outStream  << std::string(12, ' ') << "</bones>" << std::endl;
        *outStream  << std::string(10, ' ') << "</finger>" << std::endl;
    }
    *outStream << std::string(8, ' ') << "</fingers>" << std::endl;
}

void PrototypeListener::onFrame_Arm(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Hand& hand)
{
        Leap::Arm arm = hand.arm();
        *outStream   << std::string(8, ' ') << "<arm "
            << "direction=\""      << arm.direction()     << "\" "
            << "wrist_position=\"" << arm.wristPosition() << "\" "
            << "elbow_position=\"" << arm.elbowPosition() << "\" "
            << "/>"                << std::endl;
}

void PrototypeListener::onFrame_Tools(const Leap::Controller& controller, const Leap::Frame& frame)
{
    const Leap::ToolList tools = frame.tools();
    *outStream << std::string(4, ' ') << "<tools>" << std::endl;
    for (auto tl = tools.begin(); tl != tools.end(); ++tl)
    {
        const Leap::Tool tool = *tl;
        *outStream   << std::string(6, ' ') << "<tool "
            << "id=\""             << tool.id()
            << "position=\""       << tool.tipPosition() << "\" "
            << "direction=\""      << tool.direction()   << "\" "
            << "/>"                << std::endl;
    }
    *outStream << std::string(4, ' ') << "</tools>" << std::endl;
}

void PrototypeListener::onFrame_Gestures(const Leap::Controller& controller, const Leap::Frame& frame)
{
    const Leap::GestureList gestures = frame.gestures();
    *outStream << std::string(4, ' ') << "<gestures>" << std::endl;
    for (auto g = gestures.begin(); g != gestures.end() ; ++g)
    {
        const Leap::Gesture& gesture = *g;
        switch (gesture.type())
        {
            case Leap::Gesture::TYPE_CIRCLE:
                onFrame_CircleGesture(controller, frame, gesture);
                break;
            case Leap::Gesture::TYPE_SWIPE:
                onFrame_SwipeGesture(controller, frame, gesture);
                break;
            case Leap::Gesture::TYPE_KEY_TAP:
                onFrame_KeyTapGesture(controller, frame, gesture);
                break;
            case Leap::Gesture::TYPE_SCREEN_TAP:
                onFrame_ScreenTapGesture(controller, frame, gesture);
                break;
            default:
                *outStream << std::string(6, ' ')  << "<unknown_gesture />" << std::endl;
                break;
        }
    }
    *outStream << std::string(4, ' ') << "</gestures>" << std::endl;
}

void PrototypeListener::onFrame_CircleGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture)
{
    const Leap::CircleGesture& circle = gesture;
    std::string clockwiseness = (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/2)
        ? "clockwise"
        : "counterclockwise";

    float sweptAngle = 0; // Calculate angle swept since last frame
    if (circle.state() != Leap::Gesture::STATE_START)
    {
        Leap::CircleGesture previousUpdate = Leap::CircleGesture(controller.frame(1).gesture(circle.id()));
        sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Leap::PI;
    }
    *outStream << std::string(6, ' ')
              << "<circle "
              << "id=\""               << gesture.id()                  << "\" "
              << "state=\""            << stateNames[gesture.state()]   << "\" "
              << "progress=\""         << circle.progress()             << "\" "
              << "radius=\""           << circle.radius()               << "\" "
              << "angle=\""            << sweptAngle * Leap::RAD_TO_DEG << "\" "
              << "rotation_direction=" << clockwiseness                 << "\" "
              << "/>"                  << std::endl;
}

void PrototypeListener::onFrame_SwipeGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture)
{
    Leap::SwipeGesture swipe = gesture;
    *outStream << std::string(6, ' ')
              << "<swipe "
              << "id=\""             << gesture.id()                << "\" "
              << "state=\""          << stateNames[gesture.state()] << "\" "
              << "direction=\""      << swipe.direction()           << "\" "
              << "speed=\""          << swipe.speed()               << "\" "
              << "/>"                << std::endl;
}

void PrototypeListener::onFrame_KeyTapGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture)
{
    Leap::KeyTapGesture tap = gesture;
    *outStream << std::string(6, ' ')
              << "<key_tap "
              << "id=\""             << gesture.id()                << "\" "
              << "state=\""          << stateNames[gesture.state()] << "\" "
              << "position=\""       << tap.position()              << "\" "
              << "direction=\""      << tap.direction()             << "\" "
              << "/>"                << std::endl;
}

void PrototypeListener::onFrame_ScreenTapGesture(const Leap::Controller& controller, const Leap::Frame& frame, const Leap::Gesture& gesture)
{
    Leap::ScreenTapGesture screentap = gesture;
    *outStream << std::string(6, ' ')
              << "<screen_tap id=\"" << gesture.id()                << "\" "
              << "state=\""          << stateNames[gesture.state()] << "\" "
              << "position=\""       << screentap.position()        << "\" "
              << "direction=\""      << screentap.direction()       << "\" "
              << "/>"                << std::endl;
}





