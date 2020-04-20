#include "OutputController.hpp"

#include <QDebug>

OutputController::OutputController(int index)
    : Controller(index)
    , canPlay(true)
{
    taggedInstance = (DWORD) this;
    midiOutOpen(&outputHandle, index, 0, 0, CALLBACK_NULL);
}

OutputController::~OutputController()
{
    midiOutClose(outputHandle);
}

void OutputController::sendMidi(MidiMessage message)
{
    qDebug() << "Writing " << message.toString();
    if(message.isNoteOn()) 
    {
        canPlay = false;
        playing = message.byte(1);
    }
    else if(message.isNoteOff()) canPlay = true;
    
    midiOutShortMsg(outputHandle, message.param1);
}