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

#ifndef _PAL_MERGER_H_
#define _PAL_MERGER_H_
#include <map>
#include <string>
#include "color.h"

class PalMerger
{
public:
	bool parseBmp(const std::string& filename, const std::string& dir = std::string());
	bool savePalette(const std::string& filename, const std::string& dir = std::string());

	unsigned int colorToIndex(color col);

private:
	std::map<color, unsigned int> color_to_index;
};

#endif
