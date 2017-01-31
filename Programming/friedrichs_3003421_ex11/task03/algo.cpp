#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
int main(int argc, char *argv[]) {
  std::vector<std::string> param(argv + 1, argv + argc);
  std::vector<long> paramLong;

  //to long vector (because reasons)
  int i = 0;
  std::for_each(param.begin(), param.end(), [&i, &paramLong](std::string &s){
    if(i++ != 0) {
      paramLong.push_back(stoi(s));
    }
  });

  //get algorithm
  std::string algo = argv[1];
  std::ostringstream out;
  if(algo == "countodd") {
    out << std::count_if(paramLong.begin(), paramLong.end(), [](long num){ return num % 2 == 1; });
  } else if(algo == "hasnegative") {
    bool exists = std::any_of(paramLong.begin(), paramLong.end(), [](long num){ return num < 0; });
    if(exists) {
      out << "Yes";
    } else {
      out << "No";
    }
  } else if(algo == "inc") {
    std::for_each(paramLong.begin(), paramLong.end(), [&out](long &num){
      num++;
      out << num << " ";
    });
  } else if(algo == "sum") {
    int sum = 0;
    std::for_each(paramLong.begin(), paramLong.end(), [&sum](long &num){
      sum += num;
    });
    out << sum;
  } else if(algo == "deleteodd") {
    paramLong.erase(std::remove_if(paramLong.begin(), paramLong.end(), [](long x){return x % 2 != 0;}), paramLong.end());
    std::for_each(paramLong.begin(), paramLong.end(), [&out](long &num){
        out << num << " ";
    });
  }

  std::cout << out.str() << std::endl;

  return 0;
}
