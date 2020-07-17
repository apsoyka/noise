#include "configuration.h"
#include "file.h"
#include "encoder.h"

int main(int argc, char *argv[]) {
    Reader reader;
    Writer writer;
    Encoder encoder;

    // Parse command line arguments.
    Configuration::parse(argc, argv);

    // Read source file into memory.
    auto blob = reader.read();

    // Convert byte data to pixels.
    auto bitmap = encoder.encode(blob);

    // Clear input data.
    delete blob;

    // Write all image data to file.
    writer.write(bitmap);

    // Clear bitmap data.
    delete bitmap;
}