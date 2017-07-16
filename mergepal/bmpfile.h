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

#ifndef _BMP_FILE_H_
#define _BMP_FILE_H_
#include <string>
#include "color.h"

const size_t PALETTE_SIZE = 256;

class BmpFile
{
public:
	~BmpFile();

	bool load(const std::string& filename);

	const color* getPalette() const;
	const uint8_t* getPixels() const;

	size_t getWidth() const;
	size_t getHeight() const;

	uint8_t getPixel(size_t x, size_t y) const;

private:
	color palette[PALETTE_SIZE];
	uint8_t* pixel_data{ nullptr };

	size_t width, height;
};

inline const color* BmpFile::getPalette() const { return palette; }
inline const uint8_t* BmpFile::getPixels() const { return pixel_data; }

inline size_t BmpFile::getWidth() const { return width; }
inline size_t BmpFile::getHeight() const { return height; }

inline uint8_t BmpFile::getPixel(size_t x, size_t y) const { return pixel_data[y*width+x]; }

#endif
