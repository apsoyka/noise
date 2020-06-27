#include "utilities.h"

string &ltrim(string &string, const std::string characters) {
    string.erase(0, string.find_first_not_of(characters));
    return string;
}

string &rtrim(string &string, const std::string characters) {
    string.erase(string.find_last_not_of(characters) + 1);
    return string;
}

string &trim(string &string, const std::string characters) {
    return ltrim(rtrim(string, characters), characters);
}