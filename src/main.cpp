#include "file.h"
#include "parser.h"
#include "encoder.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser;
    Reader reader;
    Writer writer;
    Encoder encoder;

    // Parse command line arguments.
    parser.parse(argc, argv);

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