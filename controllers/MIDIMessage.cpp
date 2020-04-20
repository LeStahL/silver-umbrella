#include "MIDIMessage.hpp"

#include <QDebug>

MidiMessage::MidiMessage(DWORD _param1, DWORD _param2)
    : param1(_param1)
    , param2(_param2)
{
}

BYTE MidiMessage::byte(int index) const
{
    return (this->param1 >> (index*8)) & 0xFF;
}

bool MidiMessage::isNoteOn() const
{
    return this->byte(0) == 0x90;
}

bool MidiMessage::isNoteOff() const
{
    return this->byte(0) == 0x80;
}

QString MidiMessage::toString() const
{
    QString ret = "Midi message:";
    if(this->isNoteOn()) ret = "Note On:";
    if(this->isNoteOff()) ret = "Note off:";
    
    for(int i=0; i<4; ++i) ret += " 0x" + QString::number(this->byte(i), 16);
    return ret;
}
