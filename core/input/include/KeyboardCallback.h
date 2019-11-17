#pragma once

#include <InputEnums.h>
#include <vector>
#include <unordered_map>

class KeyboardListener;
class GLFWwindow;

struct KeyEvent
{
    input::keyboard::key key;
    input::keyboard::action action;
};

namespace KeyboardCallback
{
    namespace
    {
        // Contains pointers to every registered listener.
        std::vector<KeyboardListener*> listeners;

        std::unordered_map<input::keyboard::key, bool> keyStates; // Bool ? pressed : released
    }

    void registerListener(KeyboardListener* listener);
    void unregisterListener(KeyboardListener* listener);

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}