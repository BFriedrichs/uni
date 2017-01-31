#ifndef CBOT_H
#define CBOT_H

#include "Bot.hpp"

class CounterBot : public Bot {
private:
  std::vector<std::thread> _threads;
  void runTimer();

public:
  CounterBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
