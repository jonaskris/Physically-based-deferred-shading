#include <vector>
#include <unordered_map>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <KeyboardCallback.h>
#include <KeyboardListener.h>
#include <InputEnums.h>

namespace KeyboardCallback
{
    void registerListener(KeyboardListener* listener) { listeners.push_back(listener); }
    void unregisterListener(KeyboardListener* listener) { listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end()); }

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        input::keyboard::key keyEnum = static_cast<input::keyboard::key>(key);

        KeyEvent keyEvent;

        if(action == GLFW_PRESS)
        {
            keyEvent =
            {
                keyEnum,
                (keyStates[keyEnum] ? input::keyboard::action::HOLD : input::keyboard::action::PRESS)
            };

            keyStates[keyEnum] = true;
        } else if (action == GLFW_RELEASE)
        {
            keyEvent =
            {
                keyEnum,
                input::keyboard::action::RELEASE
            };        
            
            keyStates[keyEnum] = false;
        } else if (action == GLFW_REPEAT)
        {
            keyEvent =
            {
                keyEnum,
                input::keyboard::action::REPEAT
            };     
        } else 
        { 
            return; 
        }

        for(KeyboardListener* listener : listeners)
            listener->keyCallback(keyEvent);
    }
}