#include "file.h"
#include "parser.h"
#include "transcoder.h"

using namespace std;

static const auto tag = "Main";

int main(int argc, char *argv[]) {
    Parser parser;
    Reader reader;
    Writer writer;
    Transcoder transcoder;
    long buffer_size;

    // Parse command line arguments.
    parser.parse(argc, argv);

    // Read source file into memory.
    auto buffer = reader.read(&buffer_size);

    // Convert byte data to pixels.
    auto image = transcoder.transcode(buffer, buffer_size);

    delete[] buffer;

    // Write all image data to file.
    writer.write(image);
}