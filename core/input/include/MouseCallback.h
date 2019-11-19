#pragma once

#include <vector>
#include <unordered_map>

#include <InputEnums.h>
#include <Vec2.h>

class GLFWwindow;

namespace Input
{
    namespace Mouse
    {
        class PositionListener;
        class DeltaPositionListener;
        class EnterListener;
        class ButtonListener;
        class ScrollListener;

        // Events
        struct PositionEvent
        {
            math::vec2 position;

            PositionEvent(math::vec2 position) : position(position) {}
        };

        struct EnterEvent
        {
            bool entered;

            EnterEvent(bool entered) : entered(entered) {}
        };

        struct ButtonEvent
        {
            Button button;
            Action action;

            ButtonEvent(Button button, Action action) : button(button), action(action) {}
        };

        struct ScrollEvent
        {
            math::vec2 offset;

            ScrollEvent(math::vec2 offset) : offset(offset) {}
        };

        // Mouse namespace private members
        namespace
        {
            // Contains pointers to every registered listener
            std::vector<PositionListener*> positionListeners;
            std::vector<DeltaPositionListener*> deltaPositionListeners;
            std::vector<EnterListener*> enterListeners;
            std::vector<ButtonListener*> buttonListeners;
            std::vector<ScrollListener*> scrollListeners;

            // Position events
            std::vector<PositionEvent> positionEvents; 

            // DeltaPosition events
            std::vector<PositionEvent> deltaPositionEvents;
            math::vec2 lastPosition {0.5f, 0.5f}; // [0.5f, 0.5f] is the initial mouse position (Middle of screen).
            bool justEntered = false; // Used to prevent delta position being calculated when entering window, as it can yield large values when mouse leaves the window from one side and enters from another. 

            // Enter events
            std::vector<EnterEvent> enterEvents;

            // Button events
            std::unordered_map<Button, bool> buttonStates; // Bool ? pressed : released
            std::vector<ButtonEvent> buttonEvents;

            // Scroll events
            std::vector<ScrollEvent> scrollEvents;
        }

        // MouseListener registration and callback logic
        void registerListener(PositionListener* listener);
        void registerListener(DeltaPositionListener* listener);
        void registerListener(EnterListener* listener);
        void registerListener(ButtonListener* listener);
        void registerListener(ScrollListener* listener);

        void unregisterListener(PositionListener* listener);
        void unregisterListener(DeltaPositionListener* listener);
        void unregisterListener(EnterListener* listener);
        void unregisterListener(ButtonListener* listener);
        void unregisterListener(ScrollListener* listener);

        void positionCallback(GLFWwindow* window, float xpos, float ypos);
        void enterCallback(GLFWwindow* window, int entered);
        void buttonCallback(GLFWwindow* window, int button, int action, int mods);
        void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

        // Calls listeners with accumulated events
        void update(double deltatime);
    }
}