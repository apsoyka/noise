#pragma once
#include <string>
#include <vector>

using namespace std;

typedef vector <unsigned char> Blob;

struct Bitmap {
    unsigned char **pixels;
    int width, height, ppm;
};

string &ltrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &rtrim(string &string, const std::string characters = "\t\n\v\f\r ");

string &trim(string &string, const std::string characters = "\t\n\v\f\r ");