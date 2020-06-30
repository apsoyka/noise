#include "transcoder.h"
#include "configuration.h"
#include "log.h"

const string Transcoder::tag = "Transcoder";

Bitmap Transcoder::transcode(Blob blob) {
    auto width = Configuration::get_width();
    auto height = Configuration::get_height();
    auto size = blob.size();

    // Automatically determine resolution from file size if width and height aren't set.
    if (width < 1 || height < 1) {
        auto square = sqrt(size);
        auto n = ceil(square);

        width = n;
        height = n;
    }

    auto pixels = new unsigned char *[height];

    for (auto i = 0; i < height; i++)
        pixels[i] = new unsigned char[width];

    // Convert each byte to a pixel.
    for (auto x = 0; x < width; x++) {
        for (auto y = 0; y < height; y++) {
            auto a = y * width + x;
            pixels[y][x] = (a < size) ? blob[a] : 0;
        }
    }

    Log::verbose(tag, "Generated an image of " + to_string(width) + 'x' + to_string(height) + " pixels");

    return Bitmap {pixels, width, height, static_cast<int>(Configuration::get_dpi() * 39.375)};
}