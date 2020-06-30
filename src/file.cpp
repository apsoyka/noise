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
        auto f_header = file_header(file_size, offset);
        auto i_header = image_header(image.width, image.height, image.ppm);
        auto c_table = colour_table();

        // Write headers to file.
        file.write((char *)&f_header, 14);
        file.write((char *)&i_header, 40);
        file.write((char *)c_table.data(), 1024);

        // Write pixel data to file.
        for (auto y = image.height - 1; y >= 0; y--) {
            for (auto x = 0; x < image.width; x++)
                file << image.pixels[y][x];
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