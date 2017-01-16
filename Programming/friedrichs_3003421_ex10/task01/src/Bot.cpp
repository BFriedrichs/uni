#include "Bot.hpp"

void Bot::stop() {
  _isRunning = false;
}

bool Bot::isRunning() const {
  return _isRunning;
}

void Bot::addMessage(std::string message) {
  _messageBuffer.push_back(message);
}

bool Bot::hasMessage() const {
  return !_messageBuffer.empty();
}

void Bot::_printMessage(const std::string &message) {
  std::cout << _name << ": " << message << std::endl;
  _cb(message, this);
}
