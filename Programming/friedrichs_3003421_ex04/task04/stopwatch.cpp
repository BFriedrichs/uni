#include <iostream>
#include <ctime>

#ifndef SW
#define SW

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


/**
 * StopWatch constructor
 * Sets the the watch to not running
 */
StopWatch::StopWatch() {
    this->is_running = false;
}

/**
 * Starts the watch
 * Can only be called if the watch is not started yet
 * If succesful the internal state is running
 */
void StopWatch::start(void) {
    if(this->is_running) {      // check if its already running
        std::cout << "StopWatch already running!" << std::endl;
    } else {
        time = std::clock();    // save current time to "start" the clock
        this->is_running = true;
    }
}
/**
 * Stops the watch
 * Can only be called if the watch is started
 * If succesful sets the interal state to not running
 *
 * @return Passed time since start was called if the clock was running
 */
double StopWatch::stop(void) {
    if(this->is_running) {      // can only stop if its started
        this->is_running = false;
        return (clock() - this->time) / CLOCKS_PER_SEC;    // current time - start time = tracked time, CLOCKS_PER_SEC being a constant imported from time.h
    } else {
        std::cout << "StopWatch not started yet!" << std::endl;
    }
}