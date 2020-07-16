# Summary

Perform visual analysis of data entropy using this command-line tool.

# Features

- Generate a bitmap image from any input data.
- Specify resolution and dots-per-inch for generated images.
- Invert the colour palette.
- Compress images using run-length encoding.
- Scale images up or down using nearest-neighbour.

# Compression

Noise supports compressing bitmap data using the RLE8 algorithm.

Please note that, due to the [pigeonhole principle](https://en.wikipedia.org/wiki/Pigeonhole_principle), enabling compression may in fact slightly *increase* the size of the resulting bitmap file.

Only enable compression if you are sure that your input data is compressible!

# Examples

```
Algorithm : MD5
Hash      : 4187EEDF2218CE3748010E096BEA2F1F
Path      : example/random
```

![Random](images/random.bmp)

```
Algorithm : MD5
Hash      : B34E147045FDB70B6978BB9EAF0FE9C2
Path      : example/audio.wav
```

![Audio](images/audio.bmp)