#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <thread>
#include <list>
#include <vector>
#include <mutex>
#include <exception>

class Bot {
private:
  bool _isRunning = true;

protected:
  Bot(const std::string name, void (*cb)(const std::string &, Bot *pBot)) : _name(name), _cb(cb) {}
  std::string _name;
  std::list<std::string> _messageBuffer;
  void (*_cb)(const std::string &, Bot *pBot);

  std::string nextMessage();
  void _printMessage(const std::string &message);

public:
  static std::mutex bot_mutex;
  virtual void readMessage() = 0;
  void addMessage(std::string message);
  void stop();
  bool isRunning() const;
  bool hasMessage() const;

};

#endif
