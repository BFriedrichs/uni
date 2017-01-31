#include "DelayBot.hpp"

/**
 *
 * @brief Every time delayed is read print the next message 2 seconds delayed
 *
 */
void DelayBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage.find("delayed ") == 0) {
    // Cleanup MIA
    _threads.push_back(std::thread(&DelayBot::runDelay, this, currMessage));
    std::thread *t = &_threads.back();
    t->detach();
  }
}

/**
 *
 * @brief Prints message after a 2 second delay
 *
 * @param std::string, message to be delayed
 */
void DelayBot::runDelay(const std::string &currMessage) {
  int pos = currMessage.find(" ") + 1;
  std::string out = currMessage.substr(pos, currMessage.length());

  sleep(2);
  _printMessage(out);
}
