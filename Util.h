#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#define M_PI 3.14159265358979323846
class Util
{

public:
	static std::string int2str(int integer);
	static std::string flo2str(float floating);
	static float lengthdir_x( float, float );
	static float lengthdir_y( float, float );
};

#endif
