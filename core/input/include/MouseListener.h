#pragma once

#include <vector>
#include <InputEnums.h>
#include <MouseCallback.h>
#include <Vec2.h>

class MousePositionListener
{
protected:
    MousePositionListener() { MouseCallback::registerListener(this); }
    ~MousePositionListener() { MouseCallback::unregisterListener(this); }

public:
    virtual void positionCallback(math::vec2 position) = 0;
};

class MouseEnterListener
{
protected:
    MouseEnterListener() { MouseCallback::registerListener(this); }
    ~MouseEnterListener() { MouseCallback::unregisterListener(this); }

public:
    virtual void enterCallback(int entered) = 0;
};

class MouseButtonListener
{
protected:
    MouseButtonListener() { MouseCallback::registerListener(this); }
    ~MouseButtonListener() { MouseCallback::unregisterListener(this); }

public:
    virtual void buttonCallback(ButtonEvent buttonEvent) = 0;
};

class MouseScrollListener
{
protected:
    MouseScrollListener() { MouseCallback::registerListener(this); }
    ~MouseScrollListener() { MouseCallback::unregisterListener(this); }

public:
    virtual void scrollCallback(math::vec2 offset) = 0;
};