#include "encoder.h"
#include "configuration.h"
#include "log.h"

const string Encoder::tag = "Encoder";

Bitmap *Encoder::encode(Blob *blob) {
    auto width = Configuration::get_width();
    auto height = Configuration::get_height();
    auto dpi = Configuration::get_dpi();
    auto compress = Configuration::get_compression();
    auto size = blob->size();

    // Automatically determine resolution from file size if width and height aren't set.
    if (width < 1 || height < 1) {
        auto square = sqrt(size);
        auto n = ceil(square);

        width = n;
        height = n;
    }

    Bitmap *bitmap = nullptr;

    // Return an appropriately encoded bitmap image.
    if (compress)
        bitmap = encode_rle8(blob, width, height, dpi);
    else
        bitmap = encode_rgb(blob, width, height, dpi);

    Log::verbose(tag, "Generated a bitmap of %dx%d pixels with %d dots-per-inch", width, height, dpi);

    return bitmap;
}

RGBBitmap *Encoder::encode_rgb(Blob *blob, int width, int height, int dpi) {
    auto bitmap = new RGBBitmap(width, height, dpi);
    auto size = blob->size();

    // Convert each byte to a pixel.
    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            auto position = y * width + x;
            auto pixel = position < size ? blob->at(position) : 0;
            bitmap->at(x, y) = pixel;
        }
    }

    return bitmap;
}

RLE8Bitmap *Encoder::encode_rle8(Blob *blob, int width, int height, int dpi) {
    auto bitmap = new RLE8Bitmap(width, height, dpi);
    auto input_size = blob->size();

    for (auto y = 0; y < height; y++) {
        auto input = new unsigned char[width] {};

        // Read a row into memory.
        for (auto x = 0; x < width; x++) {
            auto position = y * width + x;

            input[x] = position < input_size ? blob->at(position) : 0;
        }

        auto x = 0;
        auto position = 0;

        // Iterate over a row.
        while (true) {
            auto count = 0;
            auto pixel = input[position];

            // Count the number of repeated bytes.
            while (position < width && pixel == input[position] && count < 255) {
                position++;
                count++;
            }

            bitmap->push_back(count);
            bitmap->push_back(pixel);
            x += 2;

            if (position == width)
                break;
        }

        bitmap->push_back(0);

        // Write EOL or EOF bytes.
        if (y == height -1)
            bitmap->push_back(1);
        else
            bitmap->push_back(0);

        delete[] input;
    }

    double output_size = bitmap->size();
    auto ratio = (output_size / input_size) * 100;

    Log::verbose(tag, "Encoded image using RLE8 with a ratio of %.2f%%", ratio);

    return bitmap;
}