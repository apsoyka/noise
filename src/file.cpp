#include <fstream>
#include "file.h"
#include "configuration.h"
#include "log.h"

const string Reader::tag = "Reader";
const string Writer::tag = "Writer";

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

        Log::verbose(tag, "Read %d bytes from %s", blob.size(), source.c_str());
    }

    return blob;
}

void Writer::write(Bitmap bitmap) {
    ofstream file;

    auto destination = Configuration::get_destination();

    // Open file in binary, truncate and output mode.
    file.open(destination, ios::out | ios::binary | ios::trunc);

    // Write all data to file.
    if (file.is_open()) {
        auto width = bitmap.get_width();
        auto padding = 4 - (width % 4);

        if (padding == 4)
            padding = 0;
        else
            Log::debug(tag, "Adding %d padding bytes to each row", padding);

        auto height = bitmap.get_height();
        auto bitmap_size = (width + padding) * height;
        auto offset = 14 + 40 + 1024;
        auto file_size = bitmap_size + offset;
        auto dpi = bitmap.get_dpi();
        auto ppm = dpi * 39.375;

        // Generate header data.
        auto f_header = file_header(file_size, offset);
        auto i_header = image_header(width, height, ppm);
        auto palette = colour_palette();

        // Write headers to file.
        file.write((char *)&f_header, 14);
        file.write((char *)&i_header, 40);
        file.write((char *)palette.data(), 1024);

        // Write pixel data to file.
        for (auto y = height - 1; y >= 0; y--) {
            for (auto x = 0; x < width; x++)
                file << bitmap.at(x, y);
            // Write extra padding bytes if necessary.
            if (padding)
                for (auto i = 1; i <= padding; i++)
                    file << 0;
        }

        file.close();

        Log::verbose(tag, "Wrote %d bytes to %s", file_size, destination.c_str());
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

ColourPalette Writer::colour_palette() {
    ColourPalette colour_palette {};

    auto invert = Configuration::get_invert();

    if (invert) {
        for (auto i = 0, n = 255; i < 256; i++, n--) {
            colour_palette[i].red = n;
            colour_palette[i].green = n;
            colour_palette[i].blue = n;
        }
    }
    else {
        for (auto i = 0; i < 256; i++) {
            colour_palette[i].red = i;
            colour_palette[i].green = i;
            colour_palette[i].blue = i;
        }
    }

    return colour_palette;
}