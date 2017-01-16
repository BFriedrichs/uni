#include "DelayBot.hpp"

void DelayBot::readMessage() {
  std::string currMessage = _messageBuffer.front();

  if(currMessage.find("delayed") == 0) {
    _threads.push_back(std::thread(&DelayBot::runDelay, this));
    std::thread *t = &_threads.back();
    t->detach();
  }
}

void DelayBot::runDelay() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  sleep(2);
  _printMessage(currMessage);
}
