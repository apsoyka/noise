#include "file.h"
#include "parser.h"
#include "transcoder.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser;
    Reader reader;
    Writer writer;
    Transcoder transcoder;

    // Parse command line arguments.
    parser.parse(argc, argv);

    // Read source file into memory.
    auto blob = reader.read();

    // Convert byte data to pixels.
    auto bitmap = transcoder.transcode(blob);

    // Write all image data to file.
    writer.write(bitmap);
}