#pragma once

#include "Windows.h"

#include "MIDIMessage.hpp"

void CALLBACK defaultCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

class Controller
{
    public:
    Controller(int index);

    virtual void midiEvent(MidiMessage message) = 0;

    DWORD taggedInstance;
    int controllerIndex;
};
