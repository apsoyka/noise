#include <fstream>
#include "file.h"
#include "configuration.h"
#include "log.h"

const string Reader::tag = "Reader";

Blob Reader::read() {
    ifstream file;
    Blob blob;

    auto source = Configuration::get_source();

    // Open file at the end.
    file.open(source, ios::in | ios::binary);

    // Read the file into memory.
    if (file.is_open()) {
        char byte;

        while (file.get(byte))
            blob.push_back(byte);

        file.close();

        Log::verbose(tag, "Read " + to_string(blob.size()) + " bytes from " + source);
    }

    return blob;
}

const string Writer::tag = "Writer";

void Writer::write(Bitmap bitmap) {
    ofstream file;

    auto destination = Configuration::get_destination();

    // Open file in binary, truncate and output mode.
    file.open(destination, ios::out | ios::binary | ios::trunc);

    // Write all data to file.
    if (file.is_open()) {
        auto padding = 4 - (bitmap.width % 4);

        if (padding == 4)
            padding = 0;
        else
            Log::debug(tag, "Adding " + to_string(padding) + " padding bytes to each row");

        auto bitmap_size = (bitmap.width + padding) * bitmap.height;
        auto offset = 14 + 40 + 1024;
        auto file_size = bitmap_size + offset;

        // Generate header data.
        auto f_header = file_header(file_size, offset);
        auto i_header = image_header(bitmap.width, bitmap.height, bitmap.ppm);
        auto c_table = colour_table();

        // Write headers to file.
        file.write((char *)&f_header, 14);
        file.write((char *)&i_header, 40);
        file.write((char *)c_table.data(), 1024);

        // Write pixel data to file.
        for (auto y = bitmap.height - 1; y >= 0; y--) {
            for (auto x = 0; x < bitmap.width; x++)
                file << bitmap.pixels[y][x];
            // Write extra padding bytes if necessary.
            if (padding)
                for (auto i = 1; i <= padding; i++)
                    file << 0;
        }

        file.close();

        Log::verbose(tag, "Wrote " + to_string(file_size) + " bytes to " + destination);
    }
}

FileHeader Writer::file_header(unsigned int file_size, unsigned int offset) {
    FileHeader file_header;

    file_header.file_size = file_size;
    file_header.offset = offset;

    return file_header;
}

ImageHeader Writer::image_header(signed int width, signed int height, signed int ppm) {
    ImageHeader image_header;

    image_header.width = width;
    image_header.height = height;
    image_header.horizontal_resolution = ppm;
    image_header.vertical_resolution = ppm;

    return image_header;
}

ColourTable Writer::colour_table() {
    ColourTable colour_table {};

    for (int i = 0; i < 256; i++) {
        auto n = 4 * i;

        colour_table[n] = i;
        colour_table[n + 1] = i;
        colour_table[n + 2] = i;
    }

    return colour_table;
}