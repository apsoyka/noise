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

        Log::verbose(tag, "Read " + to_string(*size) + " bytes from " + source + '.');
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
        auto image_size = image.width * image.height;
        auto file_size = 54 + 4 * image_size;

        auto f_header = file_header(file_size);
        auto i_header = image_header(image.width, image.height, file_size, image.ppm);

        file.write((char *)&f_header, 14);
        file.write((char *)&i_header, sizeof(i_header));

        for (auto i = 0; i < image_size; i++) {
            auto current = image.pixels[i];
            auto red = (current.red);
            auto green = (current.green);
            auto blue = (current.blue);
            unsigned char colour[] = {
                blue,
                green,
                red
            };
            
            file.write((char *)colour, sizeof(colour));
        }

        file.close();

        Log::verbose(tag, "Wrote " + to_string(file_size) + " bytes to " + destination + '.');
    }
}

FileHeader Writer::file_header(int size) {
    FileHeader file_header;

    memcpy(&file_header.bitmap_type, "BM", 2);
    file_header.file_size = size;
    file_header.reserved_1 = 0;
    file_header.reserved_2 = 0;
    file_header.offset = 0;

    return file_header;
}

ImageHeader Writer::image_header(int width, int height, int size, int ppm) {
    ImageHeader image_header;

    image_header.header_size = sizeof(image_header);
    image_header.width = width;
    image_header.height = -height;
    image_header.colour_planes = 1;
    image_header.colour_depth = 24;
    image_header.compression = 0;
    image_header.image_size = size;
    image_header.horizontal_resolution = ppm;
    image_header.vertical_resolution = ppm;
    image_header.colour_palette = 0;
    image_header.important_colours = 0;

    return image_header;
}