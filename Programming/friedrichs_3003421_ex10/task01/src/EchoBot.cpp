#include "EchoBot.hpp"

void EchoBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage.find("?") == -1) {
    _printMessage(currMessage + "?");
  }
}
