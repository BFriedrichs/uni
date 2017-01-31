#include <iostream>
#include <vector>
#include <map>

/**
 *
 * @brief Main method that controls the database
 * First it inputs every string with its corresponding line number into the database
 * Then it displays the line numbers corresponding to the string
 *
 **/
int main(int argc, char* argv[]) {
  std::map<std::string, std::vector<int>> database;
  std::map<std::string, std::vector<int>>::iterator dit;

  std::string input;

  int lineno = 1;
  bool isSearching = false;

  while(true) {
    getline(std::cin, input);

    if(input == ".") {
      // input / search switch
      if(isSearching) {
        break;
      } else {
        isSearching = true;
        continue;
      }
    } else {
      dit = database.find(input);
      if(isSearching) {
        if(dit == database.end()) {
          std::cout << "Not found" << std::endl;
        } else {
          //output every entry
          for(std::vector<int>::iterator it = dit->second.begin(); it != dit->second.end(); it++) {
            std::cout << *it << " ";
          }
          std::cout << std::endl;
        }
      } else {
        if(dit == database.end()) {
          //no entry
          std::vector<int> newvec;
          database[input] = newvec;
        }
        //push current lineno into the database at the location of our input string
        database[input].push_back(lineno);
      }
    }
    //increase lineno (not really needed past the switch)
    lineno++;
  }

  return 0;
}
