#include <iostream>
#include <vector>
#include "configuration.h"
#include "cxxopts.hpp"
#include "spdlog/spdlog.h"

using std::cout;
using std::endl;
using std::vector;
using cxxopts::Options;
using cxxopts::value;
using cxxopts::OptionParseException;
using spdlog::error;
using spdlog::set_level;
using spdlog::level::level_enum;

static const string tag = "Configuration";
static const string program_name = "Noise";
static const string program_description = "A visual entropy analysis tool";

static bool verbose = false;
static int width = 0;
static int height = 0;
static int dpi = 96;
static string source, destination;
static bool invert = false;
static bool compression = false;

void Configuration::parse(int argc, char *argv[]) {
    if (argc < 2)
        exit(1);

    auto options = Options(program_name, program_description);

    options.add_options()
    ("positional", "input and output file paths", value<vector<string>>());

    options.add_options("Startup")
    ("V,version", "display the version of Noise and exit")
    ("h,help", "print this help");

    options.add_options("Logging")
    ("v,verbose", "be verbose (this is the default)");

    options.add_options("Image")
    ("W,width", "the number of horizontal pixels", value<int>()->default_value("0"))
    ("H,height", "the number of vertical pixels", value<int>()->default_value("0"))
    ("D,dpi", "the number of dots-per-inch", value<int>()->default_value("96"));

    options.add_options("Format")
    ("I,invert", "invert the colour table")
    ("c,compress", "enable run-length encoding");

    options.positional_help("SOURCE DEST");
    options.parse_positional({"positional"});

    try {
        auto result = options.parse(argc, argv);
    
        if (result.count("help")) {
            cout << options.help({"", "Startup", "Logging", "Image", "Format"}) << endl;
            exit(0);
        }

        if (result.count("version")) {
            cout << "0.0.0" << endl;
            exit(0);
        }

        if (result.count("verbose"))
            set_level(level_enum::info);
        else
            set_level(level_enum::warn);

        if (result.count("width"))
            width = result["width"].as<int>();

        if (result.count("height"))
            height = result["height"].as<int>();

        if (result.count("dpi"))
            dpi = result["dpi"].as<int>();

        if (result.count("invert"))
            invert = true;

        if (result.count("compress"))
            compression = true;

        if (result.count("positional") == 2) {
            auto strings = result["positional"].as<vector<string>>();

            source = strings[0];
            destination = strings[1];
        }
        else {
            exit(1);
        }

        #ifndef NDEBUG
        set_level(level_enum::debug);
        #endif
    }
    catch (OptionParseException exception) {
        error(exception.what());
        exit(1);
    }
}

bool Configuration::get_verbose() {
    return verbose;
}

int Configuration::get_width() {
    return width;
}

int Configuration::get_height() {
    return height;
}

int Configuration::get_dpi() {
    return dpi;
}

string Configuration::get_source() {
    return source;
}

string Configuration::get_destination() {
    return destination;
}

bool Configuration::get_invert() {
    return invert;
}

bool Configuration::get_compression() {
    return compression;
}