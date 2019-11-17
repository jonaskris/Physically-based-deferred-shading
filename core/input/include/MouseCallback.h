#pragma once

#include <InputEnums.h>
#include <vector>
#include <unordered_map>
#include <Vec2.h>

class MousePositionListener;
class MouseEnterListener;
class MouseButtonListener;
class MouseScrollListener;
class GLFWwindow;

struct ButtonEvent
{
    input::mouse::button button;
    input::mouse::action action;
};

namespace MouseCallback
{
    namespace
    {
        // Contains pointers to every registered listener.
        std::vector<MousePositionListener*> positionListeners;
        std::vector<MouseEnterListener*> enterListeners;
        std::vector<MouseButtonListener*> buttonListeners;
        std::vector<MouseScrollListener*> scrollListeners;

        std::unordered_map<input::mouse::button, bool> buttonStates; // Bool ? pressed : released

        math::vec2 windowSize;
    }

    void registerListener(MousePositionListener* listener);
    void registerListener(MouseEnterListener* listener);
    void registerListener(MouseButtonListener* listener);
    void registerListener(MouseScrollListener* listener);

    void unregisterListener(MousePositionListener* listener);
    void unregisterListener(MouseEnterListener* listener);
    void unregisterListener(MouseButtonListener* listener);
    void unregisterListener(MouseScrollListener* listener);

    void positionCallback(GLFWwindow* window, float xpos, float ypos);
    void enterCallback(GLFWwindow* window, int entered);
    void buttonCallback(GLFWwindow* window, int button, int action, int mods);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
}