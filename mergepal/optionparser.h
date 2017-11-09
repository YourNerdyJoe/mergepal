#ifndef _OPTION_PARSER_H_
#define _OPTION_PARSER_H_
#include <string>

class OptionParser
{
public:
	OptionParser(const std::string& filename);
	bool parseOptions(const std::string& filename);

	size_t getMetatileWidth();
	size_t getMetatileHeight();

private:
	size_t mt_w, mt_h;
};

inline size_t OptionParser::getMetatileWidth() { return mt_w; }
inline size_t OptionParser::getMetatileHeight() { return mt_h; }

#endif
