
#include "Functions.h"


std::string int2str(int integer)
{
	std::ostringstream ss;
	ss << integer;
	return ss.str();
}
std::string flo2str(float floating)
{
	std::ostringstream ss;
	ss << floating;
	return ss.str();
}
