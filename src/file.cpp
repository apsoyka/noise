#include <fstream>
#include "file.h"
#include "configuration.h"
#include "log.h"

const string Reader::tag = "Reader";

unsigned char *Reader::read(long *size) {
    ifstream file;
    unsigned char *buffer;
    auto source = Configuration::get_source();

    // Open file at the end.
    file.open(source, ios::in | ios::binary | ios::ate);

    // Read the file into memory.
    if (file.is_open()) {
        *size = file.tellg();
        buffer = new unsigned char [*size];
        file.seekg (0, ios::beg);
        file.read ((char *)buffer, *size);
        file.close();

        Log::verbose(tag, "Read " + to_string(*size) + " bytes from " + source);
    }

    return buffer;
}

const string Writer::tag = "Writer";

void Writer::write(Image image) {
    ofstream file;
    auto destination = Configuration::get_destination();

    // Open file in binary, truncate and output mode.
    file.open(destination, ios::out | ios::binary | ios::trunc);

    // Write all data to file.
    if (file.is_open()) {
        auto padding = 4 - (image.width % 4);

        if (padding == 4)
            padding = 0;
        else
            Log::debug(tag, "Adding " + to_string(padding) + " padding bytes to each row");

        auto image_size = (image.width + padding) * image.height;
        auto offset = 14 + 40 + 1024;
        auto file_size = image_size + offset;

        // Generate header data.
        auto f_header = (char *)file_header(file_size, offset);
        auto i_header = (char *)image_header(image.width, image.height, image_size, image.ppm);
        auto c_table = (char *)colour_table();

        // Write headers to file.
        file.write(f_header, 14);
        file.write(i_header, 40);
        file.write(c_table, 1024);

        // Write pixel data to file.
        for (auto y = image.height - 1; y >= 0; y--) {
            for (auto x = 0; x < image.width; x++) {
                auto a = y * image.width + x;
                file << image.pixels[a];
            }
            // Write extra padding bytes if necessary.
            if (padding)
                for (auto i = 1; i <= padding; i++)
                    file << 0;
        }

        file.close();

        Log::verbose(tag, "Wrote " + to_string(file_size) + " bytes to " + destination);
    }
}

unsigned char *Writer::file_header(int size, int offset) {
    auto file_header = new unsigned char[14] {};

    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = size;
    file_header[3] = size >> 8;
    file_header[4] = size >> 16;
    file_header[5] = size >> 24;
    file_header[10] = offset;
    file_header[11] = offset >> 8;
    file_header[12] = offset >> 16;
    file_header[13] = offset >> 24;

    return file_header;
}

unsigned char *Writer::image_header(int width, int height, int size, int ppm) {
    auto image_header = new unsigned char[40] {};

    image_header[0] = 40;
    image_header[4] = width;
    image_header[5] = width >> 8;
    image_header[6] = width >> 16;
    image_header[7] = width >> 24;
    image_header[8] = height;
    image_header[9] = height >> 8;
    image_header[10] = height >> 16;
    image_header[11] = height >> 24;
    image_header[12] = 1;
    image_header[14] = 8;
    image_header[20] = size;
    image_header[21] = size >> 8;
    image_header[22] = size >> 16;
    image_header[23] = size >> 24;
    image_header[24] = ppm;
    image_header[25] = ppm >> 8;
    image_header[26] = ppm >> 16;
    image_header[27] = ppm >> 24;
    image_header[28] = ppm;
    image_header[29] = ppm >> 8;
    image_header[30] = ppm >> 16;
    image_header[31] = ppm >> 24;

    return image_header;
}

unsigned char *Writer::colour_table() {
    auto colour_table = new unsigned char[1024] {};

    for (int i = 0; i < 256; i++) {
        auto n = 4 * i;

        colour_table[n] = i;
        colour_table[n + 1] = i;
        colour_table[n + 2] = i;
        colour_table[n + 3] = 0;
    }

    return colour_table;
}