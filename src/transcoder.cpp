#include "transcoder.h"
#include "configuration.h"
#include "log.h"

const string Transcoder::tag = "Transcoder";

Image Transcoder::transcode(unsigned char *buffer, long buffer_size) {
    auto width = Configuration::get_width();
    auto height = Configuration::get_height();

    // Automatically determine resolution from file size if width and height aren't set.
    if (width < 1 || height < 1) {
        auto square = sqrt(buffer_size);
        auto n = ceil(square);

        width = n;
        height = n;
    }

    auto pixels = new Pixel[width * height];

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

    Log::verbose(tag, "Generated an image of " + to_string(width) + 'x' + to_string(height) + " pixels");

    return Image {pixels, width, height, static_cast<int>(Configuration::get_dpi() * 39.375)};
}