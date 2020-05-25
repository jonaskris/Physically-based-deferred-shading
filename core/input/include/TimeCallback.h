#pragma once

#include <vector>

namespace Input
{
    namespace Time
    {
        class TimeListener;

        // Events
        struct TimeEvent
        {
            double dt;
            double time;

            TimeEvent(double dt, double time) : dt(dt), time(time) {}
        };

        // FrameListener namespace private members
        namespace
        {
            // Contains pointers to every registered listener.
            std::vector<TimeListener*> listeners;
            double time = 0.0;
        }

        double getTime();

        // FrameListener registration and callback logic
        void registerListener(TimeListener* listener);
        void unregisterListener(TimeListener* listener);

        // Calls listeners with accumulated events
        void update(double deltatime);
    }
}