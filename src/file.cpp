#include <fstream>
#include "file.h"
#include "configuration.h"
#include "spdlog/spdlog.h"

using std::ifstream;
using std::ofstream;
using std::ios;
using spdlog::debug;
using spdlog::info;

const string Reader::tag = "Reader";
const string Writer::tag = "Writer";

Blob *Reader::read() {
    ifstream file;

    auto source = Configuration::get_source();
    auto blob = new Blob {};

    // Open file at the end.
    file.open(source, ios::in | ios::binary);

    // Read the file into memory.
    if (file.is_open()) {
        char byte;

        while (file.get(byte))
            blob->push_back(byte);

        file.close();

        info("Read {0:d} bytes from {1}", blob->size(), source);
    }

    return blob;
}

void Writer::write(Bitmap *bitmap) {
    ofstream file;

    auto destination = Configuration::get_destination();

    // Open file in binary, truncate and output mode.
    file.open(destination, ios::out | ios::binary | ios::trunc);

    // Write all data to file.
    if (file.is_open()) {
        auto width = bitmap->get_width();
        auto padding = 4 - (width % 4);
        auto compressed = bitmap->is_compressed();

        if (padding == 4)
            padding = 0;
        else if (!compressed)
            debug("Adding {0:d} padding bytes to each row", padding);

        auto height = bitmap->get_height();
        auto dpi = bitmap->get_dpi();
        auto ppm = dpi * 39.375;
        auto data_size = compressed ? bitmap->size() : bitmap->size() + (padding * width);
        auto offset = 14 + 40 + 1024;
        auto file_size = data_size + offset;

        // Generate header data.
        auto f_header = file_header(file_size, offset);
        auto i_header = compressed ? image_header(width, height, (int)ppm, data_size) : image_header(width, height, (int)ppm);
        auto invert = Configuration::get_invert();
        auto palette = colour_palette(invert);

        // Write headers to file.
        file.write((char *)f_header, 14);
        file.write((char *)i_header, 40);
        file.write((char *)palette->data(), 1024);

        delete f_header;
        delete i_header;
        delete palette;

        if (compressed) {
            // Write each byte of compressed data to file.
            for (auto i = 0; i < data_size; i++)
                file << bitmap->at(i);
        }
        else {
            // Write a row of pixel data to file.
            for (auto y = height - 1; y >= 0; y--) {
                // Write a column of pixel data to file.
                for (auto x = 0; x < width; x++)
                    file << bitmap->at(x, y);

                // Write extra padding bytes if necessary.
                if (padding)
                    for (auto i = 1; i <= padding; i++)
                        file << 0;
            }
        }

        file.close();

        info("Wrote {0:d} bytes to {1}", file_size, destination);
    }
}

FileHeader *Writer::file_header(unsigned int file_size, unsigned int offset) {
    auto header = new FileHeader;

    header->file_size = file_size;
    header->offset = offset;

    return header;
}

ImageHeader *Writer::image_header(signed int width, signed int height, signed int ppm) {
    auto header = new ImageHeader;

    header->width = width;
    header->height = height;
    header->horizontal_resolution = ppm;
    header->vertical_resolution = ppm;

    return header;
}

ImageHeader *Writer::image_header(signed int width, signed int height, signed int ppm, unsigned int size) {
    auto header = image_header(width, height, ppm);

    header->compression = 1;
    header->image_size = size;

    return header;
}

ColourPalette *Writer::colour_palette(bool invert) {
    auto palette = new ColourPalette {};

    if (invert) {
        for (auto i = 0, n = 255; i < 256; i++, n--) {
            auto entry = &palette->at(i);

            entry->red = n;
            entry->green = n;
            entry->blue = n;
        }
    }
    else {
        for (auto i = 0; i < 256; i++) {
            auto entry = &palette->at(i);

            entry->red = i;
            entry->green = i;
            entry->blue = i;
        }
    }

    return palette;
}