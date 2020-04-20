#pragma once

#include <QString>

#include "Windows.h"

class MidiMessage
{
    public:
    MidiMessage(DWORD param1 = 0x0, DWORD param2 = 0x0);
    BYTE byte(int index) const;

    bool isNoteOn() const;
    bool isNoteOff() const;

    QString toString() const;

    DWORD param1,
        param2;
};