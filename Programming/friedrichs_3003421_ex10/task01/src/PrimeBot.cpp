#include "PrimeBot.hpp"

/**
 *
 * @brief Every time isprime is read the following numbers are evaluated for being prime or not
 *
 */
void PrimeBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  if(currMessage.find("isprime ") == 0) {

    // tokenizing
    int pos = 0, new_pos = 0;
    while((new_pos = currMessage.find(" ", pos))) {
      int count = new_pos - pos;
      if(new_pos == std::string::npos) {
        count = currMessage.length() - pos;
      }
      std::string num = currMessage.substr(pos, count);

      if(is_digits(num)) {
        //try-catch for stoi
        try {
          // Cleanup MIA
          _threads.push_back(std::thread(&PrimeBot::runPrime, this, stoi(num)));
          std::thread *t = &_threads.back();
          t->detach();
        } catch (std::exception &e) {

        }
      }
      if(new_pos == std::string::npos) {
        break;
      }
      pos = ++new_pos;
    }
  }
}

/**
 *
 * @brief check if the number is a prime and print it
 *
 * @param int, the number to be evaluated
 */
void PrimeBot::runPrime(const int num) {
  bool is_prime = true;
  for(int i = 2; i <= sqrt(num); i++) {
    if(num % i == 0) {
      is_prime = false;
      break;
    }
  }
  std::string result = std::to_string(num) + " is ";
  if(!is_prime) {
    result += "not ";
  }
  _printMessage(result + "a prime");
}

//shamelessly copied because its way more efficient than my original method
bool PrimeBot::is_digits(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}
