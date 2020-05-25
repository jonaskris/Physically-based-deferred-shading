#include <TimeCallback.h>

#include <algorithm>

#include <TimeListener.h>

namespace Input
{
    namespace Time
    {
        // FrameListener registration and callback logic
        void registerListener(TimeListener* listener) { listeners.push_back(listener); }
        void unregisterListener(TimeListener* listener) { listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end()); }

        double getTime() { return time; }

        // Calls listeners with accumulated events
        void update(double deltatime)
        {
            const TimeEvent timeEvent(deltatime, time);
            time += deltatime;

            for(TimeListener* listener : listeners)
                listener->timeCallback(timeEvent);        
        }
    }
}