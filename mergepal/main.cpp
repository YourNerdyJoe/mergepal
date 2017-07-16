/* mergepal
* Copyright (C) 2017 Joseph LoManto
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include "palmerger.h"

void printUsage();

//convert backslashes in paths to forward slashes
static inline void replaceBackslash(std::string& str)
{ std::replace(str.begin(), str.end(), '\\', '/'); }

int main(int argc, char* argv[])
{
	int i;
	std::string pal_name("palette");
	std::string output_dir;
	color transparent_color = RGB555(31, 0, 31);	//the usual ugly purple
	
	PalMerger pal_merger;

	if(argc <= 1)
	{
		printUsage();
		return 0;
	}

	//parse options
	for(i = 1; i < argc && argv[i][0] == '-'; i++)
	{
		switch(argv[i][1])
		{
		case 'd':
			output_dir = argv[++i];
			break;

		case 'o':
			pal_name = argv[++i];
			break;

		default:
			std::cerr << "Invalid option " << argv[i] << std::endl;
			return 1;
		}
	}

	//color 0 is the transparent color
	pal_merger.colorToIndex(transparent_color);

	//parse BMP files
	for(; i < argc; i++)
	{
		std::string filename = argv[i];
		replaceBackslash(filename);
		if(!pal_merger.parseBmp(filename, output_dir))
		{
			return 1;
		}
	}

	replaceBackslash(pal_name);
	pal_merger.savePalette(pal_name, output_dir);
	std::cout << "Done.\n";

	return 0;
}

void printUsage()
{
	std::cout <<
		"mergepal [options] bmps\n"
		"\n"
		"Creates a common palette for a list of 8bpp bmp files.\n"
		"Outputs a .pal.bin for the palette, and .img.bin for each BMP's raw data.\n"
		"Color format is converted to RGB555 for use with GBA/NDS.\n"
		"BMP data is adjusted to the new palette split into 8x8 tiles.\n"
		"\n"
		"Options:\n"
		"-d [dir]\toutput directory (default: [same as BMPs])\n"
		"-o [name]\toutput palette name (default: palette)\n"
		"\n";
}
