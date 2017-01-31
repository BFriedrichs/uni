#include "QuizBot.hpp"

/**
 *
 * @brief Every time startquiz is read try to start a new quiz from the file supplied as an argument
 *
 */
void QuizBot::readMessage() {
  std::string currMessage = _messageBuffer.front();
  _messageBuffer.pop_front();

  // quiz running?
  if((currMessage.find("startquiz ") == 0 && _currentQuiz == "") ||
      (_currentQuiz != "" && currMessage == _currentAnswer)) {
    if(currMessage == _currentAnswer) {
      _printMessage("Correct!");
    } else {
      // new quiz
      int pos = currMessage.find(" ") + 1;
      std::string filename = currMessage.substr(pos, currMessage.length());
      _currentQuiz = filename;
      _index = 0;
    }

    try {
      std::ifstream file(_currentQuiz);

      std::string question;
      // scroll through file to right position
      // almost positive theres a better way to do this
      for(int i = 0; i <= _index; i++) {  
        std::getline(file, question);
      }
      std::getline(file, _currentAnswer);

      if(question != "" && _currentAnswer != "") {
        _printMessage(question);
        _index += 2;
      } else {
        _currentQuiz = "";
        _currentAnswer = "";
      }

      file.close();
    } catch(std::exception &e) {
      _currentQuiz = "";
      _currentAnswer = "";
    }
  }
}
