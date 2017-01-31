#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

enum SignalType {WLAN, BLUETOOTH};
std::string typeNames[] = {"WLAN", "BLUETOOTH"};

/**
 * @brief The Signal class represents a captured signal
 */
class Signal {
private:
    SignalType type;
    std::string deviceId;
    int strength;
    unsigned channel;

public:
    Signal(): type(WLAN){}
    SignalType getType() const {return type;}
    void setType(SignalType _type){this->type = _type;}
    std::string getDeviceId() const {return deviceId;}
    void setDeviceId(std::string _deviceId){this->deviceId = _deviceId;}
    int getStrength() const {return strength;}
    void setStrength(int _strength){this->strength = _strength;}
    unsigned getChannel() const{return channel;}
    void setChannel(unsigned _channel){this->channel = _channel;}

    friend std::ostream& operator<<(std::ostream& output, const Signal& signal);
    friend std::istream& operator>>(std::istream& input, Signal& signal);
};

//TODO: provide implementations of the overloaded I/O operators

/**
 * @brief Simply prints a Signal
 *
 * @param ostream - the output stream
 * @param Signal - the signal to be printed
 * @return ostream - << returns ostream
 */
std::ostream& operator<<(std::ostream& output, const Signal& signal) {
  output << typeNames[signal.getType()] << ", " << signal.getDeviceId() << ", " << signal.getStrength() << ", " << signal.getChannel();
  return output;
}

/**
 * @brief Reads a signal from an input stream
 *
 * @param ostream - the input stream
 * @param Signal - the signal in which the data is stored
 * @return ostream - >> returns an istream
 */
std::istream& operator>>(std::istream& input, Signal& signal) {

  char type[256];
  char deviceId[256];
  char strength[256];
  char channel[256];

  // read the attributes from the istream
  input.getline(type, 256, ',');
  input.getline(deviceId, 256, ',');
  input.getline(strength, 256, ',');
  input.getline(channel, '\n');

  // set the attributes
  if((std::string) type == "WLAN") {
      signal.setType(WLAN);
  } else {
      signal.setType(BLUETOOTH);
  }
  signal.setDeviceId(deviceId);
  signal.setStrength(atoll(strength));  // atoi wouldve worked here
  signal.setChannel(atoll(channel));    // wouldn't have worked here because channel is unsigned

  return input;
}

/**
 * @brief Reads a comma seperataed file with signals and returns a vector with all read signals
 *
 * @param char* - the file path
 * @return std::vector<Signal> - vector that contains all read signals
 */
std::vector<Signal> readSignals(const char* filepath){
  std::cout << "Reading signals from " << filepath << std::endl;
  std::vector<Signal> result;
  std::ifstream cin(filepath);
  if(!cin) return result;

  Signal sig;
  while (cin >> sig) {
    result.push_back(sig);
  }

  return result;
}

/**
 * @brief Filters all supplied signals to a certain type
 *
 * @param SignalType - the type of signal that should be filtered to
 * @param std::vector<Signal> - The full unfiltered signal list
 * @return std::vector<Signal> - The filtered signal list
 */
std::vector<Signal> filterSignals(SignalType type, std::vector<Signal>& signalReadings){
  std::vector<Signal> result;

  for(int i = 0; i < signalReadings.size(); i++) {
    Signal sig = signalReadings.at(i);
    if(sig.getType() == type) {
      result.push_back(sig);
    }
  }

  return result;
}

/**
 * @brief Writes Signals to a file
 *
 * @param char* - the output filename
 * @param std::vector<Signal> - The signals to be saved in the file
 */
void writeSignals(const char* outputFilename, const std::vector<Signal> aggregatedSignals){
  std::cout << "Writing signals to " << outputFilename << std::endl;
  std::ofstream out(outputFilename);
  if(!out) return;

  for(int i = 0; i < aggregatedSignals.size(); i++) {
    out << aggregatedSignals.at(i) << std::endl;
  }
  out.close();
}

int main(void){
    const char * filename = "signals.txt";
    std::vector<Signal> rawSignals = readSignals(filename);
    std::vector<Signal> filteredSignals = filterSignals(WLAN, rawSignals);

    std::cout << rawSignals.size() << " signals were read, of which "
              << filteredSignals.size() << " were WLAN signals!"
              << std::endl;

    writeSignals("filtered_signals.txt", filteredSignals);
    return 0;
}
