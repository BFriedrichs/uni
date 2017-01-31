#ifndef DELBOT_H
#define DELBOT_H

#include "Bot.hpp"

class DelayBot : public Bot {
private:
  std::vector<std::thread> _threads;
  void runDelay(const std::string &currMessage);

public:
  DelayBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
