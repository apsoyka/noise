#pragma once

#include <string>
#include "bitmap.h"
#include "blob.h"

using std::string;

struct Resolution {
    int width, height;
};

class Encoder {
    public:
        Bitmap *encode(Blob *);
    private:
        static const string tag;
        Bitmap *scale(Bitmap *, Resolution, Resolution, int);
        Bitmap *encode_rgb(Blob *, Resolution, int);
        Bitmap *encode_rle8(Bitmap *, int);
};