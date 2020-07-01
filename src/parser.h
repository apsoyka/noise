#pragma once

#include <vector>
#include <string>

using namespace std;

enum ExitStatus {
    SUCCESS = EXIT_SUCCESS,
    FAILURE = EXIT_FAILURE
};

class Parser {
    public:
        void parse(int, char *[]);
    private:
        int parse_int(string);
        void print(string);
        bool contains(string, vector<string>);
};

void set_exit_status(ExitStatus);

ExitStatus get_exit_status();