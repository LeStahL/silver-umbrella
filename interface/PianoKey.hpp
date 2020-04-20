#pragma once

#include <QGraphicsItem>

#include "PianoKeyboard.hpp"
#include "Controller.hpp"

class PianoKey
{
    public:
    PianoKey(int midiNote, PianoKeyboard *keyboard);

    int midiNote;
    bool on;
    PianoKeyboard *keyboard;
    QGraphicsItem *graphicsItem;
    Controller *assignedController;
};
