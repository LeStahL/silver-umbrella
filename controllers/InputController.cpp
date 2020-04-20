#include "InputController.hpp"

#include <QDebug>

void CALLBACK defaultCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    InputController *controller = (InputController *) dwInstance;
    controller->midiEvent(MidiMessage(dwParam1, dwParam2));
}

InputController::InputController(int index,  QList<OutputController *> *_outputControllers)
    : Controller(index)
    , outputControllers(_outputControllers)
{
    taggedInstance = (DWORD) this;
    midiInOpen(&inputHandle, index, (DWORD) &defaultCallback, taggedInstance, CALLBACK_FUNCTION);
    midiInStart(inputHandle);
}

InputController::~InputController()
{
    midiInClose(inputHandle);
}

void InputController::midiEvent(MidiMessage message)
{
    qDebug() << message.toString();
    if(message.isNoteOn())
    {
        for(int i=0; i<outputControllers->size(); ++i)
        {
            if(outputControllers->at(i)->canPlay)
            {
                outputControllers->at(i)->sendMidi(message);
                return;
            }
        }
    }
    else if(message.isNoteOff())
    {
        for(int i=0; i<outputControllers->size(); ++i)
        {
            if(outputControllers->at(i)->playing == message.byte(1))
            {
                outputControllers->at(i)->sendMidi(message);
                return;
            }
        }
    }
}