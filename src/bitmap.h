#pragma once

using namespace std;

class Bitmap {
    public:
        Bitmap(int, int, int);
        int get_width();
        int get_height();
        int get_dpi();
        unsigned char* data();
        unsigned char at(int, int);
        void assign(unsigned char, int, int);
    private:
        unsigned char *pixels;
        int width, height, dpi;
        int index(int x, int y);
};