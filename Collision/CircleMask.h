#ifndef CIRCLEMASK_H
#define CIRCLEMASK_H

#include "CollisionMask.h"

class CircleMask : public CollisionMask
{
private:
	int x;
	int y;
	int radius;
public:
	CircleMask(int,int,int);
};

#endif
