#pragma once

#include "Windows.h"

#include "MIDIMessage.hpp"

class Controller
{
    public:
    Controller(int index);

    DWORD taggedInstance;
    int controllerIndex;
};
