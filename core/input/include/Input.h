#pragma once

#include <InputEnums.h>
#include <KeyboardCallback.h>
#include <MouseCallback.h>
#include <KeyboardListener.h>
#include <MouseListener.h>

namespace Input
{
    // Calls Keyboard and Mouse listeners with accumulated events
    void update(double deltatime);
}