#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <vector>
#include <string>
#include "../SpriteExt.h"

class QuadtreeNode
{
private:
	int x;
	int y;
	int width;
	int height;
	static const int NODE_CAPACITY = 3; // maksymalna liczba obiektow w jednej komorce przed podzialem
	static const int MIN_SIZE = 32; // minimalna dlugosc krawedzi komorki podzialu
	QuadtreeNode** subNodes;
	std::vector<SpriteExt*> objects;
public:
	QuadtreeNode(int, int, int, int);
	~QuadtreeNode();
	void SubDivide();
	void Add(SpriteExt*);
	bool Contains(SpriteExt*);
	bool Collide(SpriteExt*);
	bool Collide(SpriteExt*, std::string);
	void Collide(SpriteExt*, std::vector<SpriteExt*>&);
	void Collide(SpriteExt*, std::vector<SpriteExt*>&, std::string);
	void Clear();
	void Display(sf::RenderWindow*,  const sf::Color = sf::Color(255,0,255));
};

#endif
