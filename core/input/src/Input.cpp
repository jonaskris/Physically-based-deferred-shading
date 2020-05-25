#include <Input.h>

namespace Input
{
    // Calls keyboard, mouse and time listeners with accumulated events
    void update(double deltatime)
    {
        Keyboard::update(deltatime);
        Mouse::update(deltatime);
        Time::update(deltatime);
    }
}