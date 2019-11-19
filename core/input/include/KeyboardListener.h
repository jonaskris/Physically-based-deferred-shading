#pragma once

#include <vector>

#include <InputEnums.h>
#include <KeyboardCallback.h>

namespace Input
{
    namespace Keyboard
    {
        class KeyListener
        {
        protected:
            KeyListener() { registerListener(this); }
            ~KeyListener() { unregisterListener(this); }

        public:
            virtual void keyCallback(double deltatime, const std::vector<KeyEvent>& keyEvents) = 0;
        };
    }
}