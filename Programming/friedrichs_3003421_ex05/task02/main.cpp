#include <iostream>

const char to_print[] = "---start---\nHello world!\n---end---";

/**
 * operator<< that writes a string (char[]) into an ostream
 *
 * @param ostream os - the ostream to be changed by << operator
 * @param char[] text - the text to be written into the ostream
 * @return ostream - the output stream
 */
std::ostream& operator<<(std::ostream &os, const char text[]) {
    if(text == "Hello world!") {
        for(char a : to_print) {
            os << a;
        }
    }

    return os;
}

int main(void) {
    std::cout << "Hello world!" << std::endl;
    return 0;
}