#ifndef DELBOT_H
#define DELBOT_H

#include "Bot.hpp"

#include <vector>

class DelayBot : public Bot {
private:
  std::vector<std::thread> _threads;
  void runDelay();

public:
  DelayBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
