#include <array>
#include "utilities.h"

using namespace std;

typedef array<unsigned char, 1024> ColourTable;

#pragma pack(push, 1)
struct FileHeader {
    unsigned char bitmap_type[2] {'B', 'M'};
    unsigned int file_size;
    unsigned short int reserved_1 {0};
    unsigned short int reserved_2 {0};
    unsigned int offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ImageHeader {
    unsigned int header_size {40};
    signed int width;
    signed int height;
    unsigned short int colour_planes {1};
    unsigned short int colour_depth {8};
    unsigned int compression {0};
    unsigned int image_size {0};
    signed int horizontal_resolution;
    signed int vertical_resolution;
    unsigned int colour_palette {0};
    unsigned int important_colours {0};
};
#pragma pack(pop)

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
        static const string tag;
        FileHeader file_header(unsigned int, unsigned int);
        ImageHeader image_header(signed int, signed int, signed int);
        ColourTable colour_table();
};