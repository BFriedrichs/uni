#ifndef PRBOT_H
#define PRBOT_H

#include "Bot.hpp"
#include <cmath>
#include <mutex>

class PrimeBot : public Bot {
private:
  std::vector<std::thread> _threads;
  void runPrime(const int num);
  bool is_digits(const std::string &str);

public:
  PrimeBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
