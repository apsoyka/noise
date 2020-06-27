#include "transcoder.h"
#include "configuration.h"
#include "log.h"

const string Transcoder::tag = "Transcoder";

Image Transcoder::transcode(unsigned char *buffer, long buffer_size) {
    int width = Configuration::get_width();
    int height = Configuration::get_height();

    // Automatically determine resolution from file size if width and height aren't set.
    if (width < 1 || height < 1) {
        auto square = sqrt(buffer_size);
        auto n = ceil(square);

        width = n;
        height = n;
    }

    int image_size = width * height;

    // Truncate extra bytes.
    if (image_size < buffer_size) {
        auto truncated = new unsigned char [image_size];
        memcpy(truncated, buffer, image_size);
        buffer = truncated;

        Log::verbose(tag, "Truncated " + to_string(buffer_size - image_size) + " bytes of data.");
    }

    auto pixels = new Pixel[image_size];

    // Convert each byte to a pixel.
    for (auto x = 0; x < width; x++) {
        for (auto y = 0; y < height; y++) {
            auto a = y * width + x;
            auto colour = (a < buffer_size) ? buffer[a] : 0;

            pixels[a].red = colour;
            pixels[a].green = colour;
            pixels[a].blue = colour;
        }
    }

    Log::verbose(tag, "Generated an image of " + to_string(width) + 'x' + to_string(height) + " pixels.");

    return Image {pixels, width, height, static_cast<int>(Configuration::get_dpi() * 39.375)};
}