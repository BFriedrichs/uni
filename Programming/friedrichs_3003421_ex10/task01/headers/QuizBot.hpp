#ifndef QZBOT_H
#define QZBOT_H

#include "Bot.hpp"

#include <fstream>

class QuizBot : public Bot {
private:
  std::string _currentQuiz;
  std::string _currentAnswer;
  int _index = 0;

public:
  QuizBot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : Bot(name, cb) {}
  virtual void readMessage();
};

#endif
