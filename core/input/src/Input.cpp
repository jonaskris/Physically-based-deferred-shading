#include <Input.h>

namespace Input
{
    // Calls Keyboard and Mouse listeners with accumulated events
    void update(double deltatime)
    {
        Keyboard::update(deltatime);
        Mouse::update(deltatime);
    }
}