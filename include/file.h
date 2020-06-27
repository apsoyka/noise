#include "utilities.h"

using namespace std;

struct FileHeader {
    unsigned char bitmap_type[2];
    int file_size;
    short reserved_1;
    short reserved_2;
    unsigned int offset;
};

struct ImageHeader {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    short int colour_planes;
    short int colour_depth;
    unsigned int compression;
    unsigned int image_size;
    unsigned int horizontal_resolution;
    unsigned int vertical_resolution;
    unsigned int colour_palette;
    unsigned int important_colours;
};

class Reader {
    public:
        unsigned char *read(string, long *);
};

class Writer {
    public:
        void write(string, Image);
    private:
        FileHeader file_header(int);
        ImageHeader image_header(int, int, int, int);
};