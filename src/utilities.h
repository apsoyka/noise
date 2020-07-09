#pragma once

#include <string>

using std::string;

string &ltrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &rtrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &trim(string &string, const std::string characters = "\t\n\v\f\r ");