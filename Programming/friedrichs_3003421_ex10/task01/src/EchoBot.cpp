#include "EchoBot.hpp"

/**
 *
 * @brief Repeats the read message and adds a "?" if there is none in it yet
 *
 */
void EchoBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage.find("?") == -1) {
    _printMessage(currMessage + "?");
  }
}
