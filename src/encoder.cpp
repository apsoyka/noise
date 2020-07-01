#include "encoder.h"
#include "configuration.h"
#include "log.h"

const string Encoder::tag = "Encoder";

Bitmap Encoder::encode(Blob blob) {
    auto width = Configuration::get_width();
    auto height = Configuration::get_height();
    auto dpi = Configuration::get_dpi();
    auto size = blob.size();

    // Automatically determine resolution from file size if width and height aren't set.
    if (width < 1 || height < 1) {
        auto square = sqrt(size);
        auto n = ceil(square);

        width = n;
        height = n;
    }

    auto bitmap = Bitmap(width, height, dpi);

    // Convert each byte to a pixel.
    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto n = y * width + x;
            auto pixel = n < size ? blob[n] : 0;
            bitmap.assign(pixel, x, y);
        }
    }

    Log::verbose(tag, "Generated a bitmap of %dx%d pixels with %d dots-per-inch", width, height, dpi);

    return bitmap;
}