#include "configuration.h"

static bool verbose = false;
static int width = 0;
static int height = 0;
static int dpi = 96;
static string source, destination;

bool Configuration::get_verbose() {
    return verbose;
}

void Configuration::set_verbose(bool value) {
    verbose = value;
}

int Configuration::get_width() {
    return width;
}

void Configuration::set_width(int value) {
    width = value;
}

int Configuration::get_height() {
    return height;
}

void Configuration::set_height(int value) {
    height = value;
}

int Configuration::get_dpi() {
    return dpi;
}

void Configuration::set_dpi(int value) {
    dpi = value;
}

string Configuration::get_source() {
    return source;
}

void Configuration::set_source(string value) {
    source = value;
}

string Configuration::get_destination() {
    return destination;
}

void Configuration::set_destination(string value) {
    destination = value;
}