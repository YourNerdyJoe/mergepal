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

#ifndef _COLOR_H_
#define _COLOR_H_
#include <stdint.h>

typedef uint16_t color;
typedef uint32_t color32;

color color32To16(color32 col);

inline color RGB555(uint8_t r, uint8_t g, uint8_t b) { return (color)(r) | (g << 5) | (b << 10); }

#endif
