#include "transcoder.h"

Image Transcoder::transcode(unsigned char *buffer, long buffer_size, int width, int height, int dpi) {
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

    return Image {pixels, width, height, dpi};
}