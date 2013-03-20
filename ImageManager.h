#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <map>
#include <string>
#include <SFML/Graphics.hpp>


class ImageManager
{
	private:
	
	static ImageManager* INSTANCE;
	std::map<std::string, sf::Image> images;
	
	public:
	
	static ImageManager* getInstance();
	sf::Image loadImage( std::string filename );
};

#endif
