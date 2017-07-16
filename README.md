mergepal
========
Creates a common palette for a list of 8bpp bmp files.
Outputs a .pal.bin for the palette, and .img.bin for each BMP's raw data.
Color format is converted to RGB555 for use with GBA/NDS.
BMP data is adjusted to the new palette split into 8x8 tiles.

Usage
-----
mergepal [options] bmps

Options
-------
- -d [dir]\toutput directory (default: [same as BMPs])
- -o [name]\toutput palette name (default: palette)
