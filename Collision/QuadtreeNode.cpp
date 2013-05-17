#include "QuadtreeNode.h"
#include <cstdlib>
#include <algorithm>
#include "CollisionMask.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GameEngine.h"

QuadtreeNode::QuadtreeNode(int nx, int ny, int w, int h) : x(nx), y(ny), width(w), height(h), subNodes(NULL)
{
}

void QuadtreeNode::SubDivide()
{
	if( subNodes == NULL )
	{
		subNodes = new QuadtreeNode*[4];
		subNodes[0] = new QuadtreeNode( x, y, width/2, height/2 );
		subNodes[1] = new QuadtreeNode( x + width/2, y, width/2, height/2 );
		subNodes[2] = new QuadtreeNode( x, y + height/2, width/2, height/2 );
		subNodes[3] = new QuadtreeNode( x + width/2, y + height/2, width/2, height/2 );
	}
	else
	{
		for ( int i = 0; i < 4; i++ )
			subNodes[i]->SubDivide();
	}
}

bool QuadtreeNode::Contains( SpriteExt* spr )
{
	CollisionMask* mask = spr->getCollisionMask();

	if ( mask == NULL )
		return false;

	if ( mask->getType() == BOX )
	{
		int x1 = spr->GetPosition().x-spr->GetCenter().x+((BoxMask*)mask)->getRect().Left;
		int x2 = spr->GetPosition().x-spr->GetCenter().x+((BoxMask*)mask)->getRect().Right;
		int y1 = spr->GetPosition().y-spr->GetCenter().y+((BoxMask*)mask)->getRect().Top;
		int y2 = spr->GetPosition().y-spr->GetCenter().y+((BoxMask*)mask)->getRect().Bottom;
		if ( x1 >= x && x2 <= x+width && y1 >= y && y2 <= y+height )
			return true;
		else return false;
	}
	else if ( mask->getType() == CIRCLE )
	{
		int x1 = spr->GetPosition().x-spr->GetCenter().x+((CircleMask*)mask)->getX();
		int y1 = spr->GetPosition().y-spr->GetCenter().y+((CircleMask*)mask)->getY();
		int r = ((CircleMask*)mask)->getRadius();
		if ( x1-r >= x && x1+r <= x+width && y1-r >= y && y1+r <= y+height )
			return true;
		else return false;
	}

	return false;
}

void QuadtreeNode::Add( SpriteExt* spr )
{
	if ( subNodes != NULL )
	{
		for ( int i = 0; i < 4; i++ )
			if ( subNodes[i]->Contains(spr) )
			{
				subNodes[i]->Add(spr);
				return;
			}
	}

	objects.push_back(spr);

	if ( subNodes == NULL && objects.size() > NODE_CAPACITY && std::min(width/2, height/2) >= MIN_SIZE )
	{
		SubDivide();
		for ( int j = 0; j < objects.size(); j++ )
			for ( int i = 0; i < 4; i++ )
				if ( subNodes[i]->Contains(objects[j]) )
				{
					subNodes[i]->Add(objects[j]);
					objects.erase(objects.begin()+j);
					j--;
					break;
				}
	}

	//std::cout << "subNodes = " << subNodes << std::endl;

}

bool QuadtreeNode::Collide(SpriteExt* spr)
{
	for ( int i = 0; i < objects.size(); i++ )
		if ( objects[i] != spr && GameEngine::Collision(spr,objects[i]) )
			return true;

	if ( subNodes != NULL )
		for ( int i = 0; i < 4; i++ )
			if ( subNodes[i]->Collide(spr) )
				return true;

	return false;

}

bool QuadtreeNode::Collide(SpriteExt* spr, std::string type)
{
	for ( int i = 0; i < objects.size(); i++ )
		if ( objects[i] != spr && objects[i]->getType() == type && GameEngine::Collision(spr,objects[i]) )
			return true;

	if ( subNodes != NULL )
		for ( int i = 0; i < 4; i++ )
			if ( subNodes[i]->Collide(spr, type) )
				return true;

	return false;

}

void QuadtreeNode::Collide(SpriteExt* spr, std::vector<SpriteExt*>& results)
{
	for ( int i = 0; i < objects.size(); i++ )
		if ( objects[i] != spr && GameEngine::Collision(spr,objects[i]) )
			results.push_back(objects[i]);

	if ( subNodes != NULL )
		for ( int i = 0; i < 4; i++ )
			subNodes[i]->Collide(spr, results);
}

void QuadtreeNode::Collide(SpriteExt* spr, std::vector<SpriteExt*>& results, std::string type)
{
	for ( int i = 0; i < objects.size(); i++ )
		if ( objects[i] != spr && objects[i]->getType() == type && GameEngine::Collision(spr,objects[i]) )
			results.push_back(objects[i]);

	if ( subNodes != NULL )
		for ( int i = 0; i < 4; i++ )
			subNodes[i]->Collide(spr, results, type);
}

void QuadtreeNode::Display(sf::RenderWindow* window, const sf::Color color)
{
	sf::Shape rect = sf::Shape::Rectangle(((float)x),
										  ((float)y),
										  ((float)x+width),
										  ((float)y+width),
										  sf::Color(0,0,0,0),
										  1.f,
										  color );
	window->Draw(rect);
	if ( subNodes != NULL )
		for ( int i = 0; i < 4; i++ )
			subNodes[i]->Display(window);
}

void QuadtreeNode::Clear()
{
	objects.clear();
	if ( subNodes != NULL )
	{
		for ( int i = 0; i < 4; i++ )
			delete subNodes[i];
		delete []subNodes;
		subNodes = NULL;
	}
}

QuadtreeNode::~QuadtreeNode()
{
	Clear();
}
