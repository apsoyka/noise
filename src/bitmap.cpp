#include "bitmap.h"

Bitmap::~Bitmap() {
    delete pixels;
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

Blob *Bitmap::data() {
    return pixels;
}

Blob *Bitmap::slice(int start, int end) {
    return new Blob(pixels->cbegin() + start, pixels->cbegin() + end + 1);
}

unsigned char &Bitmap::at(int i) {
    return pixels->at(i);
}

unsigned char &Bitmap::at(int x, int y) {
    auto position = index(x, y);
    return pixels->at(position);
}

void Bitmap::push_back(unsigned char byte) {
    pixels->push_back(byte);
}

int Bitmap::index(int x, int y) {
    return x + width * y;
}

RGBBitmap::RGBBitmap(int width, int height, int dpi) {
    this->width = width;
    this->height = height;
    this->dpi = dpi;
    pixels = new Blob(width * height);
}

int RGBBitmap::size() {
    return width * height;
}

bool RGBBitmap::is_compressed() {
    return false;
}

RLE8Bitmap::RLE8Bitmap(int width, int height, int dpi) {
    this->width = width;
    this->height = height;
    this->dpi = dpi;
    pixels = new Blob;
}

int RLE8Bitmap::size() {
    return pixels->size();
}

bool RLE8Bitmap::is_compressed() {
    return true;
}