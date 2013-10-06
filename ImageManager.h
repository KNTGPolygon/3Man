#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Singleton.h"


class ImageManager : public Singleton<ImageManager>
{
private:
	std::map<std::string, sf::Image> images;
	sf::Image image_blank;
	
public:
	sf::Image& loadImage( std::string filename );
};

#endif
