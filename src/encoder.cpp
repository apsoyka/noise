#include "encoder.h"
#include "configuration.h"
#include "spdlog/spdlog.h"

using spdlog::info;

Bitmap *Encoder::encode(Blob *blob) {
    auto dpi = Configuration::get_dpi();
    auto width = Configuration::get_width();
    auto height = Configuration::get_height();
    auto compress = Configuration::get_compression();

    // Automatically determine resolution from file size if width and height aren't set.
    auto size = blob->size();
    auto square = sqrt(size);
    auto rounded = ceil(square);
    auto resolution = Resolution {(int)rounded, (int)rounded};

    // Generate an RGB bitmap from the input bytes.
    Bitmap *bitmap = encode_rgb(blob, resolution, dpi);

    // Scale the generated bitmap if necessary.
    if ((width != rounded || height != rounded) && (width > 0 && height > 0)) {
        auto original = resolution;

        resolution = Resolution {width, height};

        auto scaled = scale(bitmap, original, resolution);

        delete bitmap;

        bitmap = scaled;
    }

    // Return an appropriately encoded bitmap image.
    if (compress) {
        auto compressed = encode_rle8(bitmap);

        delete bitmap;

        bitmap = compressed;
    }

    info("Generated a bitmap of {0:d}x{1:d} pixels and {2:d} dots-per-inch", resolution.width, resolution.height, dpi);

    return bitmap;
}

Bitmap *Encoder::scale(Bitmap *input, Resolution original, Resolution scaled) {
    auto output = new RGBBitmap(scaled.width, scaled.height, input->get_dpi());
    auto x_ratio = (double)original.width / (double)scaled.width;
    auto y_ratio = (double)original.height / (double)scaled.height;
    double px, py; 

    for (auto y = 0; y < scaled.height; y++) {
        for (int x = 0; x < scaled.width; x++) {
            px = floor(x * x_ratio);
            py = floor(y * y_ratio);
            output->at(x, y) = input->at((int)px, (int)py);
        }
    }

    auto ratio = ((double)scaled.width / (double)original.width) * ((double)scaled.height / (double)original.height) * 100;

    info("Scaled the bitmap image by {0:.2f}%", ratio);

    return output;
}

Bitmap *Encoder::encode_rgb(Blob *input, Resolution resolution, int dpi) {
    auto output = new RGBBitmap(resolution.width, resolution.height, dpi);
    auto size = input->size();

    // Convert each byte to a pixel.
    for (auto y = 0; y < resolution.height; y++) {
        for (auto x = 0; x < resolution.width; x++) {
            auto position = y * resolution.width + x;
            auto pixel = position < (int)size ? input->at(position) : 0;

            output->at(x, y) = (unsigned char)pixel;
        }
    }

    return output;
}

Bitmap *Encoder::encode_rle8(Bitmap *input) {
    auto input_size = input->size();
    auto width = input->get_width();
    auto height = input->get_height();
    auto output = new RLE8Bitmap(width, height, input->get_dpi());

    for (auto y = height - 1; y >= 0; y--) {
        auto start = y * width;
        auto end = start + width - 1;
        auto row = input->slice(start, end);
        auto count = 0;

        for (auto x = 0; x < width; x += count) {
            count = 0;

            // Count the number of repeated bytes.
            while (x + count < width && count < 255 && row->at(x + count) == row->at(x))
                count++;

            output->push_back(count);
            output->push_back(row->at(x));
        }

        // Write end of line bytes.
        output->push_back(0);
        output->push_back(0);

        delete row;
    }

    // Write end of file bytes.
    output->push_back(0);
    output->push_back(1);

    auto output_size = output->size();
    auto ratio = ((double)output_size / (double)input_size) * 100;

    info("Encoded image using RLE8 with a ratio of {0:.2f}%", ratio);

    return output;
}