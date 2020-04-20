#include "InputController.hpp"

#include <QDebug>

InputController::InputController(int index)
    : Controller(index)
{
    taggedInstance = (DWORD) this;
    midiInOpen(&inputHandle, index, (DWORD) &defaultCallback, taggedInstance, CALLBACK_FUNCTION);
    midiInStart(inputHandle);
}

void InputController::midiEvent(MidiMessage message)
{
    qDebug() << message.toString();
}