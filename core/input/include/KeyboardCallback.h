#pragma once

#include <vector>
#include <unordered_map>

#include <InputEnums.h>

class GLFWwindow;

namespace Input
{
    namespace Keyboard
    {
        class KeyListener;

        // Events
        struct KeyEvent
        {
            Key key;
            Action action;

            KeyEvent(Key key, Action action) : key(key), action(action) {}
        };

        // Keyboard namespace private members
        namespace
        {
            // Contains pointers to every registered listener.
            std::vector<KeyListener*> listeners;

            std::unordered_map<Key, bool> keyStates; // Bool ? pressed : released
            std::vector<KeyEvent> keyEvents;
        }

        // KeyListener registration and callback logic
        void registerListener(KeyListener* listener);
        void unregisterListener(KeyListener* listener);

        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // Calls listeners with accumulated events
        void update(double deltatime);
    }
}