#pragma once

#include "Controller.hpp"

class InputController : public Controller
{
    public:
    InputController(int index);

    void midiEvent(MidiMessage message) override;

    HMIDIIN inputHandle;
};