#pragma once

#include <TimeCallback.h>

namespace Input
{
    namespace Time
    {
        class TimeListener
        {
        protected:
            TimeListener() { registerListener(this); }
            ~TimeListener() { unregisterListener(this); }

        public:
            virtual void timeCallback(const TimeEvent& timeEvent) = 0;
        };
    }
}