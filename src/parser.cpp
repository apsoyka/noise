#include <iostream>
#include "parser.h"
#include "configuration.h"
#include "utilities.h"

static const string usage_simple = R"(
Usage: noise [OPTION]... SOURCE DEST

Try 'noise --help' for more options.
)";

static const string usage_full = R"(
Noise 0.0.0, a visual entropy analysis tool.
Usage: noise [OPTION]... SOURCE DEST

Mandatory arguments to long options are mandatory for short options too.

General:
  -h,  --help           print this help
  -V,  --version        display the version of Noise and exit
  -v,  --verbose        print verbose output

Format:
  -W,  --width=WIDTH    set the width in pixels of the image to generate
  -H,  --height=HEIGHT  set the height in pixels of the image to generate
  -D,  --dpi=DPI        set the dots-per-inch of the image to generate
  -i,  --invert         invert the colour table
  -c,  --compress       enable RLE compression
)";

static ExitStatus exit_status;

void Parser::parse(int argc, char *argv[]) {
    vector<string> arguments;
    vector<string> files;

    if (argc <= 1) {
        print("noise: missing file operand");
        print(usage_simple);
    }

    // Convert c style strings.
    for (auto i = 1; i < argc; i++)
        arguments.push_back(argv[i]);

    // Perform pattern matching.
    for (auto iterator = arguments.begin(); iterator != arguments.end(); iterator++) {
        auto argument = *iterator;

        if (contains(argument, {"-h", "--help"})) {
            print(usage_full);
            exit(exit_status);
        }
        else if (contains(argument, {"-V", "--version"})) {
            print("0.0.0");
            exit(exit_status);
        }
        else if (contains(argument, {"-v", "--verbose"}))
            Configuration::set_verbose(true);
        else if (contains(argument, {"-W", "--width"})) {
            auto n = parse_int(argument);
            if (n > 0) Configuration::set_width(n);
        }
        else if (contains(argument, {"-H", "--height"})) {
            auto n = parse_int(argument);
            if (n > 0) Configuration::set_height(n);
        }
        else if (contains(argument, {"-D", "--dpi"})) {
            auto n = parse_int(argument);
            if (n > 0) Configuration::set_dpi(n);
        }
        else if (contains(argument, {"-i", "--invert"}))
            Configuration::set_invert(true);
        else if (contains(argument, {"-c", "--compress"}))
            Configuration::set_compression(true);
        else
            files.push_back(argument);
    }

    Configuration::set_source(files[0]);
    Configuration::set_destination(files[1]);
}

int Parser::parse_int(string string) {
    auto position = string.find('=');
    auto substring = string.substr(position + 1);
    return stoi(substring);
}

void Parser::print(string string) {
    cout << trim(string) << endl;
}

bool Parser::contains(string query, vector<string> list) {
    for (auto iterator = list.begin(); iterator != list.end(); iterator++) {
        auto contains = query.find(*iterator) != string::npos;
        if (contains)
            return true;
    }
    return false;
}

void set_exit_status(ExitStatus status) {
    if (exit_status) {
        if (status < exit_status) {
            exit_status = status;
        }
        else {
            exit_status = status;
        }
    }
}

ExitStatus get_exit_status() {
    return exit_status;
}