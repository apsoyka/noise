#include "file.h"
#include "parser.h"
#include "transcoder.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser;
    Reader reader;
    Writer writer;
    Transcoder transcoder;
    long buffer_size;

    // Parse command line arguments.
    auto configuration = parser.parse(argc, argv);

    // Read source file into memory.
    auto buffer = reader.read(configuration.source, &buffer_size);

    // Convert byte data to pixels.
    auto image = transcoder.transcode(buffer, buffer_size, configuration.width, configuration.height, configuration.dpi);

    delete[] buffer;

    // Write all image data to file.
    writer.write(configuration.destination, image);
}