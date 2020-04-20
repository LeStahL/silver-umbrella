#pragma once

#include "Controller.hpp"

class OutputController : public Controller
{
    public:
    OutputController(int index);
    ~OutputController();

    void sendMidi(MidiMessage message);

    bool canPlay;
    BYTE playing;
    HMIDIOUT outputHandle;
};