#pragma once

#include <vector>
#include "blob.h"

class Bitmap {
    public:
        ~Bitmap();
        int get_width();
        int get_height();
        int get_dpi();
        Blob *data();
        unsigned char &at(int);
        unsigned char &at(int, int);
        void push_back(unsigned char);
        virtual int size() = 0;
        virtual bool is_compressed() = 0;
    protected:
        Blob *pixels;
        int width, height, dpi;
        int index(int, int);
};

class RGBBitmap : public Bitmap {
    public:
        RGBBitmap(int, int, int);
        int size();
        bool is_compressed();
};

class RLE8Bitmap : public Bitmap {
    public:
        RLE8Bitmap(int, int, int);
        int size();
        bool is_compressed();
};