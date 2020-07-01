#pragma once

#include <string>
#include "bitmap.h"
#include "blob.h"

using namespace std;

class Encoder {
    public:
        Bitmap encode(Blob);
    private:
        static const string tag;
};