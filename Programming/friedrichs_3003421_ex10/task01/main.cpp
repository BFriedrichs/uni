#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>

#include "Bot.hpp"
#include "EchoBot.hpp"
#include "CounterBot.hpp"
#include "DelayBot.hpp"
#include "PrimeBot.hpp"
#include "QuizBot.hpp"

enum BOT_TYPE {ECHO, COUNTER, DELAY, PRIME, QUIZ, TYPE_SIZE};
static const std::string BOT_TYPE_NAMES[] = {"echo", "counter", "delay", "prime", "quiz"};

std::vector<Bot *> registeredBots;
std::vector<std::thread> threads;

pid_t pid = 0;

void runBot(Bot *bot);
void broadcastMessage(const std::string &message, Bot *pBot = NULL);
Bot *createBot(const std::string name, const BOT_TYPE type);

/**
 *
 * @brief shutdown the bots and join back to main thread then exit after six second sleep
 *
 */
void shutdown() {
  sleep(6);

  for(std::vector<Bot *>::iterator it = registeredBots.begin(); it != registeredBots.end(); it++) {
    (*it)->stop();
  }

  for(std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); it++) {
    (*it).join();
  }

  exit(1);
}

/**
 *
 * @brief Main method - handles user input / bot creation
 *
 */
int main(int argc, char *argv[]) {
  bool isRunning = true;

  while(isRunning) {
    std::string input;
    std::getline(std::cin, input);

    if(input.find("bot:") == 0) {
      Bot *newBot;

      for(int i = 0; i < BOT_TYPE::TYPE_SIZE; i++) {
        if(input.find(BOT_TYPE_NAMES[i]) == 4) {
          std::string name = input.substr(input.find(',') + 1);
          newBot = createBot(name, static_cast<BOT_TYPE>(i));
          break;
        }
      }
      if(newBot == NULL) {
        // if bot creation fails just handle it as a regular message
        broadcastMessage(input);
      } else {
        registeredBots.push_back(newBot);
        threads.push_back(std::thread(runBot, newBot));
      }
    } else if(input == "exit") {
      shutdown();
    } else {
      broadcastMessage(input);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}

/**
 *
 * @brief Broadcasts a message to every bot (is used as a callback for every bot)
 *
 * @param std::string, Message to be broadcasted
 * @param Bot *, Pointer to Bot that sends the message
 */
void broadcastMessage(const std::string &message, Bot *pBot) {
  for(std::vector<Bot *>::iterator it = registeredBots.begin(); it != registeredBots.end(); it++) {
    if(*it != pBot) {
      (*it)->addMessage(message);
    }
  }
}

/**
 *
 * @brief Only is used from created thread.
 * Constantly looks for new messages in the bots message queue and reads it if there is one
 *
 * @param Bot *, Pointer to Bot that wil be running
 */
void runBot(Bot *bot) {
  while(bot->isRunning()) {
    if(bot->hasMessage()) {
      bot->readMessage();
    }
  }
}

/**
 *
 * @brief Only is used from created thread.
 * Constantly looks for new messages in the bots message queue and reads it if there is one
 *
 * @param std::string, Name for the bot
 * @param BOT_TYPE, bot type
 *
 * @return Bot *, Pointer to the just created bot
 */
Bot *createBot(const std::string name, const BOT_TYPE type) {
  Bot *newBot;
  if(name != "") {
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
      case BOT_TYPE::PRIME:
        newBot = new PrimeBot(name, &broadcastMessage);
        break;
      case BOT_TYPE::QUIZ:
        newBot = new QuizBot(name, &broadcastMessage);
        break;
      default:
        break;
    }
  }

  return newBot;
}
