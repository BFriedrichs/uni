#include "Bot.hpp"

std::mutex Bot::bot_mutex;

/**
 *
 * @brief Sets the running flag to false which subsequently just ends the bot
 *
 */
void Bot::stop() {
  _isRunning = false;
}

/**
 *
 * @brief Is the bot running?
 *
 * @return bool
 */
bool Bot::isRunning() const {
  return _isRunning;
}

/**
 *
 * @brief Adds a message to the bots message queue
 *
 * @param std::string, message to be added
 */
void Bot::addMessage(std::string message) {
  _messageBuffer.push_back(message);
}

/**
 *
 * @brief Are there any new messages?
 *
 * @return bool, new messages?
 */
bool Bot::hasMessage() const {
  return !_messageBuffer.empty();
}

/**
 *
 * @brief Prints the message to output and calls the callback for the broadcast
 * Uses mutex multiple threads cant write to output at the same time
 *
 * @param std::string, message to be printed
 */
void Bot::_printMessage(const std::string &message) {
  Bot::bot_mutex.lock();

  std::stringstream result;
  result << _name << ": " << message;
  std::cout << result.str() << std::endl;
  _cb(message, this);

  Bot::bot_mutex.unlock();
}
