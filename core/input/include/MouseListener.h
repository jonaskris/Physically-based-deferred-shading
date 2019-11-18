#pragma once

#include <vector>
#include <InputEnums.h>
#include <MouseCallback.h>
#include <Vec2.h>

namespace Input
{
    namespace Mouse
    {
        class PositionListener
        {
        protected:
            PositionListener() { registerListener(this); }
            ~PositionListener() { unregisterListener(this); }

        public:
            virtual void positionCallback(double deltatime, const std::vector<PositionEvent>& positionEvents) = 0;
        };

        class DeltaPositionListener
        {
        protected:
            DeltaPositionListener() { registerListener(this); }
            ~DeltaPositionListener() { unregisterListener(this); }

        public:
            virtual void deltaPositionCallback(double deltatime, const std::vector<PositionEvent>& deltaPositionEvents) = 0;
        };

        class EnterListener
        {
        protected:
            EnterListener() { registerListener(this); }
            ~EnterListener() { unregisterListener(this); }

        public:
            virtual void enterCallback(double deltatime, const std::vector<EnterEvent>& enterEvents) = 0;
        };

        class ButtonListener
        {
        protected:
            ButtonListener() { registerListener(this); }
            ~ButtonListener() { unregisterListener(this); }

        public:
            virtual void buttonCallback(double deltatime, const std::vector<ButtonEvent>& buttonEvents) = 0;
        };

        class ScrollListener
        {
        protected:
            ScrollListener() { registerListener(this); }
            ~ScrollListener() { unregisterListener(this); }

        public:
            virtual void scrollCallback(double deltatime, const std::vector<ScrollEvent>& scrollEvents) = 0;
        };
    }
}