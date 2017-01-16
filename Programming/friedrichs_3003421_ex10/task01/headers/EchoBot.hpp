#ifndef EBOT_H
#define EBOT_H

#include "Bot.hpp"

class EchoBot : public Bot {
public:
  EchoBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
