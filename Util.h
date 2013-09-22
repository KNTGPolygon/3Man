#ifndef UTIL_H
#define UTIL_H
#include <sstream>

class Util
{
public:
	static std::string int2str(int integer);
	static std::string flo2str(float floating);
	static float lengthdir_x( float, float );
	static float lengthdir_y( float, float );
};

#endif
