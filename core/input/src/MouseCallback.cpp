#include <vector>
#include <unordered_map>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <MouseCallback.h>

#include <MouseListener.h>
#include <InputEnums.h>
#include <Vec2.h>

namespace Input
{
    namespace Mouse
    {
        // MouseListener registration and callback logic
        void registerListener(PositionListener* listener) { positionListeners.push_back(listener); }
        void registerListener(DeltaPositionListener* listener) { deltaPositionListeners.push_back(listener); }
        void registerListener(EnterListener* listener) { enterListeners.push_back(listener); }
        void registerListener(ButtonListener* listener) { buttonListeners.push_back(listener); }
        void registerListener(ScrollListener* listener) { scrollListeners.push_back(listener); }

        void unregisterListener(PositionListener* listener) { positionListeners.erase(std::remove(positionListeners.begin(), positionListeners.end(), listener), positionListeners.end()); }
        void unregisterListener(DeltaPositionListener* listener) { deltaPositionListeners.erase(std::remove(deltaPositionListeners.begin(), deltaPositionListeners.end(), listener), deltaPositionListeners.end()); }
        void unregisterListener(EnterListener* listener) { enterListeners.erase(std::remove(enterListeners.begin(), enterListeners.end(), listener), enterListeners.end()); }
        void unregisterListener(ButtonListener* listener) { buttonListeners.erase(std::remove(buttonListeners.begin(), buttonListeners.end(), listener), buttonListeners.end()); }
        void unregisterListener(ScrollListener* listener) { scrollListeners.erase(std::remove(scrollListeners.begin(), scrollListeners.end(), listener), scrollListeners.end()); }

        void positionCallback(GLFWwindow* window, float xpos, float ypos)
        {
            positionEvents.emplace_back(math::vec2{xpos, ypos});

            if(!justEntered)
                deltaPositionEvents.emplace_back(math::vec2{xpos, ypos} - lastPosition);

            lastPosition = math::vec2{xpos, ypos};
            justEntered = false;
        }

        void enterCallback(GLFWwindow* window, int entered)
        {
            enterEvents.emplace_back((bool)entered);

            if(entered)
                justEntered = true;
        }

        void buttonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            Button buttonEnum = static_cast<Button>(button);

            if(action == GLFW_PRESS)
            {
                buttonEvents.emplace_back
                (
                    buttonEnum,
                    Action::PRESS
                );      

                buttonStates[buttonEnum] = true;
            } else if (action == GLFW_RELEASE)
            {
                buttonEvents.emplace_back
                (
                    buttonEnum,
                    Action::RELEASE
                );        

                buttonStates[buttonEnum] = false;
            }
        }

        void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
            scrollEvents.emplace_back(math::vec2{(float)xoffset, (float)yoffset});        
        }

        // Calls listeners with accumulated events
        void update(double deltatime)
        {
            for(auto& buttonstate : buttonStates)
                if(buttonstate.second)
                    buttonEvents.emplace_back
                    (
                        buttonstate.first,
                        Action::HOLD
                    );    

            for(PositionListener* listener : positionListeners)
                listener->positionCallback(deltatime, positionEvents);        

            for(DeltaPositionListener* listener : deltaPositionListeners)
                listener->deltaPositionCallback(deltatime, deltaPositionEvents);   

            for(EnterListener* listener : enterListeners)
                listener->enterCallback(deltatime, enterEvents);          

            for(ButtonListener* listener : buttonListeners)
                listener->buttonCallback(deltatime, buttonEvents);

            for(ScrollListener* listener : scrollListeners)
                listener->scrollCallback(deltatime, scrollEvents);

            positionEvents.clear();
            deltaPositionEvents.clear();
            enterEvents.clear();
            buttonEvents.clear();
            scrollEvents.clear();
        }
    }
}