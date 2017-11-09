#include "optionparser.h"
#include <fstream>
#include <iostream>

OptionParser::OptionParser(const std::string& filename)
	: mt_w(1)
	, mt_h(1)
{
	parseOptions(filename);
}

bool OptionParser::parseOptions(const std::string& filename)
{
	std::ifstream opt_file(filename);

	if(!opt_file.is_open()) return false;

	std::cout << "Found option file " << filename << "\n";

	opt_file >> mt_w;
	opt_file >> mt_h;
	return true;
}
