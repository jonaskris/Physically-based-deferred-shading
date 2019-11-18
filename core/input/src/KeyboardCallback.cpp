#include <vector>
#include <unordered_map>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <KeyboardCallback.h>
#include <KeyboardListener.h>
#include <InputEnums.h>

namespace Input
{
    namespace Keyboard
    {
        // KeyListener registration and callback logic
        void registerListener(KeyListener* listener) { listeners.push_back(listener); }
        void unregisterListener(KeyListener* listener) { listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end()); }

        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Key keyEnum = static_cast<Key>(key);

            if(action == GLFW_PRESS)
            {
                keyEvents.emplace_back
                (
                    keyEnum,
                    Action::PRESS
                );

                keyStates[keyEnum] = true;
            } else if (action == GLFW_RELEASE)
            {
                keyEvents.emplace_back
                (
                    keyEnum,
                    Action::RELEASE
                );

                keyStates[keyEnum] = false;
            } else if (action == GLFW_REPEAT)
            {
                keyEvents.emplace_back
                (
                    keyEnum,
                    Action::REPEAT
                );
            }
        }

        // Calls listeners with accumulated events
        void update(double deltatime)
        {
            for(auto& keystate : keyStates)
                if(keystate.second)
                    keyEvents.emplace_back
                    (
                        keystate.first,
                        Action::HOLD
                    );

            for(KeyListener* listener : listeners)
                listener->keyCallback(deltatime, keyEvents);        

            keyEvents.clear();
        }
    }
}