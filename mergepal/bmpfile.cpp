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

#include "bmpfile.h"
#include <fstream>
#include <iostream>

const long BMP_HEADER_OFFSET = 0;
const long BMP_DATA_OFFSET = 10;
const long BMP_WIDTH_OFFSET = 18;
const long BMP_HEIGHT_OFFSET = 22;
const long BMP_BPP_OFFSET = 28;
const long BMP_PAL_OFFSET = 54;	//after header info

BmpFile::~BmpFile()
{
	if(pixel_data) delete[] pixel_data;
}

template<class T> static inline void readVarFromFile(std::ifstream& file, T& var, long ofs)
{
	file.seekg(ofs);
	file.read((char*)&var, sizeof(T));
}

bool BmpFile::load(const std::string& filename)
{
	char bmp_header[2];
	uint32_t bmp_pixel_ofs;
	uint32_t bmp_width, bmp_height;
	uint16_t bmp_bpp;

	color32 bmp_palette[PALETTE_SIZE];

	std::ifstream bmp_file(filename, std::ios::binary);

	if(!bmp_file.is_open())
	{
		std::cout << "error\n";
		std::cerr << "Unable to open " << filename << "\n";
		return false;
	}

	//get header
	readVarFromFile(bmp_file, bmp_header, BMP_HEADER_OFFSET);

	//check if header is valid
	if(!(bmp_header[0] == 'B' && bmp_header[1] == 'M'))
	{
		std::cout << "error\n";
		std::cerr << filename << " is not a valid BMP file.\n";
		return false;
	}

	readVarFromFile(bmp_file, bmp_bpp, BMP_BPP_OFFSET);

	//must be 8bpp
	if(bmp_bpp != 8)
	{
		std::cout << "error\n";
		std::cerr << filename << " is not a 256 color BMP.\n";
		return false;
	}

	//load other vars
	readVarFromFile(bmp_file, bmp_pixel_ofs, BMP_DATA_OFFSET);
	readVarFromFile(bmp_file, bmp_width, BMP_WIDTH_OFFSET);
	readVarFromFile(bmp_file, bmp_height, BMP_HEIGHT_OFFSET);

	width = bmp_width;
	height = bmp_height;

	//load palette
	readVarFromFile(bmp_file, bmp_palette, BMP_PAL_OFFSET);

	for(int i = 0; i < PALETTE_SIZE; i++)
	{
		palette[i] = color32To16(bmp_palette[i]);
	}

	//load pixel data
	pixel_data = new uint8_t[width*height];

	bmp_file.seekg(bmp_pixel_ofs);
	bmp_file.read((char*)pixel_data, width*height);

	return true;
}
