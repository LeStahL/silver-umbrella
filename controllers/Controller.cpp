#include "Controller.hpp"

void CALLBACK defaultCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    Controller *controller = (Controller *) dwInstance;
    controller->midiEvent(MidiMessage(dwParam1, dwParam2));
}

Controller::Controller(int _index)
    : controllerIndex(_index)
{
}