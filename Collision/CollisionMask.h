/*
 * CollisionMask.h
 *
 */

#ifndef COLLISIONMASK_H
#define COLLISIONMASK_H

enum MASKTYPE { BOX, CIRCLE };

class CollisionMask
{
protected:
	MASKTYPE type;
public:
	MASKTYPE getType();
	void setType(MASKTYPE);
};

#endif
