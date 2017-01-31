#include "CounterBot.hpp"

/**
 *
 * @brief Every time startcounter is read it starts a new thread that counts up to 3
 *
 */
void CounterBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage == "startcounter") {
    // Cleanup MIA
    _threads.push_back(std::thread(&CounterBot::runTimer, this));
    std::thread *t = &_threads.back();
    t->detach();  // detach because we dont really want to join
  }
}

/**
 *
 * @brief Thread that runs for 3 seconds and prints 1-3
 *
 */
void CounterBot::runTimer() {
  for(int i = 0; i < 3; i++) {
    _printMessage(std::to_string(i + 1));
    sleep(1);
  }
}
