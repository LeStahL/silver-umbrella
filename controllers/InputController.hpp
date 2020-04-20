#pragma once

#include <QList>

#include "Controller.hpp"
#include "OutputController.hpp"

void CALLBACK defaultCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

class InputController : public Controller
{
    public:
    InputController(int index, QList<OutputController *> *outputControllers);
    ~InputController();

    void midiEvent(MidiMessage message);

    HMIDIIN inputHandle;
    QList<OutputController *> *outputControllers;
};