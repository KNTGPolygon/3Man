#include "Util.h"
#include <cmath>

std::string Util::int2str(int integer)
{
	std::ostringstream ss;
	ss << integer;
	return ss.str();
}
std::string Util::flo2str(float floating)
{
	std::ostringstream ss;
	ss << floating;
	return ss.str();
}

float Util::lengthdir_x( float len, float dir )
{
	return len*cos((float)dir*(M_PI/180));
}

float Util::lengthdir_y( float len, float dir )
{
	return len*sin((float)dir*(M_PI/180));
}
