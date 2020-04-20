#pragma once

#include <QList>

#include "Controller.hpp"
#include "PianoKey.hpp"
#include "PianoKeyboardGraphicsItem.hpp"
#include "PianoKeyGraphicsItem.hpp"

class PianoKeyboard
{
    public:
    PianoKeyboard(int lowerKeyLimit, int upperKeyLimit, Controller *assignedController = nullptr);

    int nKeys();

    int lowerKeyLimit,
        upperKeyLimit;
    QList<PianoKey *> keys;

};

