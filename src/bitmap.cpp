#include "bitmap.h"

Bitmap::Bitmap(int width, int height, int dpi) {
    this->width = width;
    this->height = height;
    this->dpi = dpi;
    pixels = new unsigned char[width * height] {};
}

int Bitmap::get_width() {
    return width;
}

int Bitmap::get_height() {
    return height;
}

int Bitmap::get_dpi() {
    return dpi;
}

unsigned char *Bitmap::data() {
    return pixels;
}

unsigned char Bitmap::at(int x, int y) {
    auto position = index(x, y);
    return pixels[position];
}

void Bitmap::assign(unsigned char pixel, int x, int y) {
    auto position = index(x, y);
    pixels[position] = pixel;
}

int Bitmap::index(int x, int y) {
    return x + width * y;
}