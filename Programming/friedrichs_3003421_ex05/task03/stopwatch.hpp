#include <ctime>

#ifndef SW_H
#define SW_H

/**
 * \class StopWatch
 *
 * StopWatch class to stop the time
 *
 */
class StopWatch {
    private:
        std::clock_t time;  // start time
        bool is_running;    // bool to check if clock is alread running

    public:
        StopWatch();
        void start(void);
        double stop(void);
};

#endif