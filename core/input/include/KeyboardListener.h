#pragma once

#include <vector>
#include <InputEnums.h>
#include <KeyboardCallback.h>

class KeyboardListener
{
protected:
    KeyboardListener() { KeyboardCallback::registerListener(this); }
    ~KeyboardListener() { KeyboardCallback::unregisterListener(this); }

public:
    virtual void keyCallback(const KeyEvent keyEvent) = 0;
};