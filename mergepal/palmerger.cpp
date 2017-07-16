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

#include "palmerger.h"
#include <fstream>
#include <iostream>
#include "bmpfile.h"

static inline std::string replaceExtAndDir(const std::string& filename, const std::string& ext, const std::string& dir)
{
	//replace file extension
	std::string ret = filename.substr(0, filename.find_last_of('.')) + ext;

	//change directory if provided
	if(!dir.empty())
	{
		//remove existing path
		size_t end_file_path = ret.find_last_of('/');
		if(end_file_path == std::string::npos)
			end_file_path = 0;
		else
			end_file_path++;

		//insert new path
		ret = dir + "/" + ret.substr(end_file_path);
	}

	return ret;
}

bool PalMerger::parseBmp(const std::string& filename, const std::string& dir)
{
	BmpFile bmp;

	//filename of output
	std::string img_filename = replaceExtAndDir(filename, ".img.bin", dir);

	std::cout << filename << " -> ";

	if(bmp.load(filename))
	{
		auto palette = bmp.getPalette();

		size_t width = bmp.getWidth();
		size_t height = bmp.getHeight();

		size_t tile_width = width / 8;
		size_t tile_height = height / 8;

		std::ofstream img_file(img_filename, std::ios::binary);

		//split into 8x8 tiles
		for(size_t tile_y = 0; tile_y < tile_height; tile_y++)
		{
			for(size_t tile_x = 0; tile_x < tile_width; tile_x++)
			{
				for(size_t y = 0; y < 8; y++)
				{
					for(size_t x = 0; x < 8; x++)
					{
						//add color to palette if not there
						//then write new index to file
						//error if too many colors in palette

						uint8_t col_idx = bmp.getPixel(tile_x * 8 + x, tile_y * 8 + y);
						unsigned int common_pal_idx = colorToIndex(palette[col_idx]);
						if(common_pal_idx >= PALETTE_SIZE)
						{
							std::cout << "error\n";
							std::cerr << "Palette has exceeded 256 colors\n";
							return false;
						}
						else
						{
							img_file.write((const char*)&common_pal_idx, 1);
						}
					}
				}
			}
		}

		std::cout << img_filename << std::endl;

		return true;
	}
	else
	{
		return false;
	}
	
}

bool PalMerger::savePalette(const std::string& filename, const std::string& dir)
{
	color palette[PALETTE_SIZE];

	//clear palette
	memset(palette, 0, sizeof(palette));

	//map to array
	for(auto& kv : color_to_index)
	{
		palette[kv.second] = kv.first;
	}

	//filename
	std::string pal_filename = replaceExtAndDir(filename, ".pal.bin", dir);

	//save to file
	std::ofstream pal_file(pal_filename, std::ios::binary);

	pal_file.write((char*)palette, sizeof(palette));

	return false;
}

unsigned int PalMerger::colorToIndex(color col)
{
	//check if color is already in the palette
	//otherwise add it and return the index
	auto it = color_to_index.find(col);
	if(it == color_to_index.end())
	{
		unsigned int next_idx = color_to_index.size();

		color_to_index[col] = next_idx;
		return next_idx;
	}
	else
	{
		return it->second;
	}
}
