#include "utilities.h"

using namespace std;

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
        unsigned char *file_header(int);
        unsigned char *image_header(int, int, int, int);
        unsigned char *colour_table();
        static const string tag;
};