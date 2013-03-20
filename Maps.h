#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Tile.h"

#ifndef MAPS_H
#define MAPS_H

#include <sstream>

class Maps{

private:
	std::vector<std::string> addresses;
	std::vector<std::vector<Tile> > m_data;
	


public:
	Maps(const std::string& filename);
	void showMap();
	void getTileGraphicsAddressesSet(std::string str);


};

#endif