#include "CounterBot.hpp"

void CounterBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage == "startcounter") {
    std::thread t(&CounterBot::runTimer, this);
    t.detach();
  }
}

void CounterBot::runTimer() {
  for(int i = 0; i < 3; i++) {
    _printMessage(std::to_string(i));
    sleep(1);
  }
  exit(1);
}
