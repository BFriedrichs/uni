#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "Bot.hpp"
#include "EchoBot.hpp"
#include "CounterBot.hpp"
#include "DelayBot.hpp"

enum BOT_TYPE {ECHO, COUNTER, DELAY, PRIME, QUIZ, TYPE_SIZE};
static const std::string BOT_TYPE_NAMES[] = {"echo", "counter", "delay", "prime", "quiz"};

std::vector<Bot *> registeredBots;
std::vector<std::thread> threads;
std::mutex bot_mutex;

pid_t pid = 0;

void runBot(Bot *bot);
void broadcastMessage(const std::string &message, Bot *pBot = NULL);
Bot *createBot(const std::string name, const BOT_TYPE type);

void shutdown() {
  exit(1);
}

void sig_handler(int signo) {
  shutdown();
}

int main(int argc, char *argv[]) {
  bool isRunning = true;

  signal(SIGINT, sig_handler);

  while(isRunning) {
    std::string input;
    std::getline(std::cin, input);

    if(input.find("bot:") == 0) {
      Bot *newBot;

      for(int i = 0; i < BOT_TYPE::TYPE_SIZE; i++) {
        if(input.find(BOT_TYPE_NAMES[i]) == 4) {
          std::string name = input.substr(input.find(',') + 1);
          newBot = createBot(name, static_cast<BOT_TYPE>(i));
        }
      }

      registeredBots.push_back(newBot);
      threads.push_back(std::thread(runBot, newBot));
    } else if(input == "exit") {
      sleep(6);

      for(std::vector<Bot *>::iterator it = registeredBots.begin(); it != registeredBots.end(); it++) {
        (*it)->stop();
      }

      shutdown();
    } else {
      broadcastMessage(input);
    }
  }

  return 0;
}

void broadcastMessage(const std::string &message, Bot *pBot) {
  for(std::vector<Bot *>::iterator it = registeredBots.begin(); it != registeredBots.end(); it++) {
    if(*it != pBot) {
      (*it)->addMessage(message);
    }
  }
}

void runBot(Bot *bot) {
  while(bot->isRunning()) {
    if(bot->hasMessage()) {
      bot_mutex.lock();
      bot->readMessage();
      bot_mutex.unlock();
    }
  }
  exit(1);
}

Bot *createBot(const std::string name, const BOT_TYPE type) {
  Bot *newBot;

  switch(type) {
    case BOT_TYPE::ECHO:
      newBot = new EchoBot(name, &broadcastMessage);
      break;
    case BOT_TYPE::COUNTER:
      newBot = new CounterBot(name, &broadcastMessage);
      break;
    case BOT_TYPE::DELAY:
      newBot = new DelayBot(name, &broadcastMessage);
      break;
    case BOT_TYPE::QUIZ:

      break;
    default:
      break;
  }

  return newBot;
}
