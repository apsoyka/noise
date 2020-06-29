#include <array>
#include "utilities.h"

using namespace std;

typedef array<unsigned char, 1024> ColourTable;

class Reader {
    public:
        unsigned char *read(long *);
    private:
        static const string tag;
};

class Writer {
    public:
        void write(Image);
    private:
        unsigned char *file_header(int, int);
        unsigned char *image_header(int, int, int, int);
        ColourTable colour_table();
        static const string tag;
};