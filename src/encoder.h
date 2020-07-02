#pragma once

#include <string>
#include "bitmap.h"
#include "blob.h"

using namespace std;

class Encoder {
    public:
        Bitmap *encode(Blob *);
    private:
        static const string tag;
        RGBBitmap *encode_rgb(Blob *, int, int, int);
        RLE8Bitmap *encode_rle8(Blob *, int, int, int);
};