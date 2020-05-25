#pragma once

#include <InputEnums.h>
#include <KeyboardCallback.h>
#include <MouseCallback.h>
#include <TimeCallback.h>
#include <KeyboardListener.h>
#include <MouseListener.h>
#include <TimeListener.h>

namespace Input
{
    // Calls keyboard, mouse and time listeners with accumulated events
    void update(double deltatime);
}