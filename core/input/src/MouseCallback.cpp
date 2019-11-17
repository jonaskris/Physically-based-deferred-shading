#include <vector>
#include <unordered_map>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <MouseListener.h>
#include <MouseCallback.h>
#include <InputEnums.h>
#include <Vec2.h>

namespace MouseCallback
{
    void registerListener(MousePositionListener* listener) { positionListeners.push_back(listener); }
    void registerListener(MouseEnterListener* listener) { enterListeners.push_back(listener); }
    void registerListener(MouseButtonListener* listener) { buttonListeners.push_back(listener); }
    void registerListener(MouseScrollListener* listener) { scrollListeners.push_back(listener); }

    void unregisterListener(MousePositionListener* listener) { positionListeners.erase(std::remove(positionListeners.begin(), positionListeners.end(), listener), positionListeners.end()); }
    void unregisterListener(MouseEnterListener* listener) { enterListeners.erase(std::remove(enterListeners.begin(), enterListeners.end(), listener), enterListeners.end()); }
    void unregisterListener(MouseButtonListener* listener) { buttonListeners.erase(std::remove(buttonListeners.begin(), buttonListeners.end(), listener), buttonListeners.end()); }
    void unregisterListener(MouseScrollListener* listener) { scrollListeners.erase(std::remove(scrollListeners.begin(), scrollListeners.end(), listener), scrollListeners.end()); }

    void windowResizeCallback(int width, int height)
    {
        windowSize = math::vec2{width, height};
    }

    void positionCallback(GLFWwindow* window, float xpos, float ypos)
    {
        for(MousePositionListener* listener : positionListeners)
            listener->positionCallback(math::vec2{xpos, ypos});
    }

    void enterCallback(GLFWwindow* window, int entered)
    {
        for(MouseEnterListener* listener : enterListeners)
            listener->enterCallback(entered);        
    }

    void buttonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        input::mouse::button buttonEnum = static_cast<input::mouse::button>(button);

        ButtonEvent buttonEvent;

        if(action == GLFW_PRESS)
        {
            buttonEvent =
            {
                buttonEnum,
                (buttonStates[buttonEnum] ? input::mouse::action::HOLD : input::mouse::action::PRESS)
            };

            buttonStates[buttonEnum] = true;
        } else if (action == GLFW_RELEASE)
        {
            buttonEvent =
            {
                buttonEnum,
                input::mouse::action::RELEASE
            };        
            
            buttonStates[buttonEnum] = false;
        } else 
        { 
            return; 
        }

        for(MouseButtonListener* listener : buttonListeners)
            listener->buttonCallback(buttonEvent);
    }

    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        for(MouseScrollListener* listener : scrollListeners)
            listener->scrollCallback(math::vec2{(float)xoffset, (float)yoffset});        
    }
}