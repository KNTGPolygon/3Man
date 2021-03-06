#include "PathFinder.h"
#include "../GameEngine.h"

PathFinder::PathFinder(void)
{
	gridCellSize = 32;
	closedListMarker = 0;
	loaded = false;
	std::cout<<"PathFinder constructor online !\n";
}
PathFinder::~PathFinder(void)
{
}
void PathFinder::Cleanup()
{
	for( int i = 0 ; i < gridXSize ; i++ )
			delete cell[i];
	delete openList;
	pathStatus.resize(0);
	pathLength.resize(0);
}
OpenList::OpenList( int gridXSize, int gridYSize )
{
	totalSize = gridXSize * gridYSize;
	IDList = new int[ totalSize ];
	HCost  = new int[ totalSize ];
	FCost  = new int[ totalSize ];
	pointCoords = new sf::Vector2i[ totalSize ];
	size = 0;
}
OpenList::~OpenList(void)
{
	delete IDList;
	delete FCost;
	delete HCost;
}
void OpenList::AddPointToList( sf::Vector2i point, int newItemFcost )
{
	if ( size <= totalSize )
	{
	if( size == 0 )
	{
	IDList[ size ] = size;
	pointCoords[ size ] = point;
	FCost[ size ] = newItemFcost;
	}else
	{
		int tmp1 = 0;
		int tmp2 = size-1;
		int tmp3 = 0;
		int oldtmp1 = -1;
		int oldtmp2 = -1;
		bool found = false;
		do{
			
			//std::cout<<"adding..\n";
			//std::cout<<tmp1<<" "<<tmp2<<std::endl;
			//std::cout<<FCost[tmp1]<<" "<<FCost[tmp2]<<std::endl;
		if( tmp1 == tmp2 || oldtmp1 == tmp1 || oldtmp2 == tmp2)
		{
			found = true;
		}
		tmp3 = ( tmp1+tmp2 ) / 2;
		if( newItemFcost > FCost[tmp3] ) //lista uporzadkowana rosnaco
		{
			oldtmp1 = tmp1;
			tmp1 = tmp3 + 1;
		} else if( newItemFcost < FCost[tmp3])
		{
			oldtmp2 = tmp2;
			tmp2 = tmp3 - 1 ;
		}
		else if( newItemFcost == FCost[tmp3] )
		{
			found = true;
			tmp1 = tmp3;
			tmp2 = tmp3;
		}
		}while( !found );

		for( int i = size - 1 ; i >tmp1 ; i-- )
		{
			FCost[i] = FCost[i - 1];
			HCost[i] = HCost[i - 1];
			pointCoords[i] = pointCoords[i - 1];

		}
		if( newItemFcost > FCost[size-1] )
		{
			FCost[ size-1 ] = newItemFcost;
			pointCoords[ size-1 ] = point;
			IDList[ size-1 ] = size-1;
			IDList[ size ] = size;
		}
		else
		{
		IDList[ size ] = size;
		FCost[tmp1] = newItemFcost;
		pointCoords[tmp1] = point;
		//HCost[tmp1] = newItemHcost;
		}
	}

	size++;
	}
	else
		std::cout<<"openList overwritten\n";
}
void OpenList::AddNewFCostAndSort( int pointID, int newFCost )
{


	int tempFcost;
	sf::Vector2i tempPointCoords;
	FCost[ pointID ] = newFCost;

		if( pointID != size - 1 )
		{
		if( FCost[ pointID ] >= FCost[ pointID + 1 ] ) // tu mozliwy bond
		{
			for( int i = pointID ; i < size ; i++ )
			{
				if( FCost[ i ] > FCost[ i + 1 ] )
				{
					tempPointCoords = pointCoords[ i + 1 ];
					tempFcost = FCost[ i + 1 ];
					FCost[ i + 1 ] = FCost[ i ];
					pointCoords[ i + 1 ] = pointCoords[ i ];
					FCost[ i ] =  tempFcost;
					pointCoords[ i ] = tempPointCoords;

				}
				else break;
			 
			}
		}
	else
	
	{
		for(int i = pointID ; i >= 1; i-- )
		{
			if( FCost[ i ] < FCost[ i - 1 ] )
			{
				tempPointCoords = pointCoords[ i - 1]; // i+1 bylo
				tempFcost = FCost[ i - 1 ];
				FCost[ i - 1 ] = FCost[ i ];
				pointCoords[ i - 1 ] = pointCoords[ i ];
				FCost[ i ] =  tempFcost;
				pointCoords[ i ] = tempPointCoords;
			}
		}
	}
		}
		else
		{
			for(int i = pointID ; i >= 1; i-- ) // do zera
			{
				if( FCost[ i ] < FCost[ i - 1 ] )
				{
					tempPointCoords = pointCoords[ i - 1 ];  // i + 1 bylo
					tempFcost = FCost[ i - 1 ];
					FCost[ i - 1 ] = FCost[ i ];
					pointCoords[ i - 1 ] = pointCoords[ i ];
					FCost[ i ] =  tempFcost;
					pointCoords[ i ] = tempPointCoords;
				}
			}

		}
}
void OpenList::EreseFromList(  int pointID )
{
	if( size > 1 )
	{
		for( int i = pointID ; i < size ; i++ )
		{
			pointCoords[ i ] = pointCoords[ i + 1 ];
			HCost[ i ] = HCost[ i + 1 ];
			FCost[ i ] = FCost[ i + 1 ];
		}
		IDList[ pointID ] = pointID;
	}
	else if( size == 0 )
	{
		size = 0;
	}

	size--;

}
int OpenList::GetLowestFCostPointID()
{
	//return IDList[ 0 ];
	return 0;
}
int OpenList::GetPointID( sf::Vector2i point )
{
	for( int i = 0 ; i < size ; i++ )
	{
		if( pointCoords[i] == point )
			return i;
	}
}
void PathFinder::Initialization(std::vector<sf::Vector3i> objectList, int _gridXSize, int _gridYSize)
{
	if(loaded == true )
	{
			Cleanup();
	}
	gridXSize = _gridXSize;
	gridYSize = _gridYSize;
	loaded = true;

	openList = new OpenList( gridXSize , gridYSize );

	cell = new Cell*[ gridXSize ];
	for( int i = 0 ; i < gridXSize ; i++ )
	cell[i] = new Cell[ gridYSize ];

	for( int i = 0 ; i < gridXSize ; i ++ )
	{
		for( int j = 0 ; j < gridYSize ; j++ )
		{
			cell[i][j].walkability = WALKABLE;
		}
	}
	for( int i = 0 ; i < objectList.size() ; i ++ )
	{
		cell[ objectList[i].y ][ objectList[i].x ].walkability = UNWALKABLE; // zamieniam x -> y , y - >x 
	}
}
int PathFinder::FindPath(int pathfinderID, sf::Vector2i _start, sf::Vector2i _target)
{
	int thisPointID;
	int counter;
	sf::Vector2i thisPoint;

	start  = sf::Vector2i( _start.x / gridCellSize   , _start.y / gridCellSize ); 
	target = sf::Vector2i( _target.x / gridCellSize  , _target.y /gridCellSize );  

	//Sprawdz czy nie szukano juz takiej drogi/ czy jest / czy nie stoje na targecie	

	//if (start.x == target.x && start.y == target.y && pathLength[pathfinderID] > 0)
		//return FOUND;
	if (start.x == target.x && start.y == target.y && pathLength[pathfinderID] == 0)
		return NONEXISTENT;

	if ( cell[target.x][target.y].walkability == UNWALKABLE )
		goto noPath;


	closedListMarker = closedListMarker + 2; 
	openListMarker = closedListMarker - 1;
	
	openList->size = 0;
	openList->AddPointToList( start, 0 );

	cell[ start.x ][ start.y ].whichList = openListMarker;
	cell[ start.x ][ start.y ].GCost = 0;
	cell[ start.x ][ start.y ].HCost = 0;
	cell[ start.x ][ start.y ].FCost = 0;
	cell[ start.x ][ start.y ].parent = sf::Vector2i( 0 , 0 );

	counter = 0;
	do{
		if( openList->size != 0 )
		{
			thisPointID = openList->GetLowestFCostPointID();
			thisPoint   = openList->pointCoords[ thisPointID ];

			cell[ thisPoint.x ][ thisPoint.y ].whichList = closedListMarker; 

			openList->EreseFromList( thisPointID );

			SearchPointsArround( thisPoint );
		}
		else
		{
			//std::cout<<"not-found\n"; //do testow
			pathStatus[ pathfinderID ] = NONEXISTENT; break;
		}
		if ( cell[target.x][target.y].whichList == openListMarker )
		{
			//std::cout<<"found\n";		//do testow
			pathStatus[ pathfinderID ] = FOUND; break;
		}

	counter++;
	}while(1);
	//std::cout<<"Total loops made : "<<counter<<std::endl; //do testow

	if( pathStatus[ pathfinderID ] == FOUND )
	{
		pathStatus[ pathfinderID ] = SaveFoundedPath( pathfinderID ,  start );
	}
	return pathStatus[ pathfinderID ];
noPath:

	foundedCoords[ pathfinderID ] = _start;
	return NONEXISTENT;

}
void PathFinder::ErasePointFromOpenList(int pointID)
{
	sf::Vector2i thisPoint = openList->pointCoords[pointID];
	openList->EreseFromList( pointID );
	cell[thisPoint.x][thisPoint.y].whichList = closedListMarker;

}
void PathFinder::SearchPointsArround( sf::Vector2i thisPoint )
{
	int addedGCost = 0;
	int corner = 0;

	for (int  y = thisPoint.y-1; y <= thisPoint.y+1; y++)
	{
		for (int  x = thisPoint.x-1; x <= thisPoint.x+1; x++)
		{
			if (x != -1 && y != -1 && x != gridXSize && y != gridYSize)
			{
				if ( cell[x][y].whichList   != closedListMarker &&
					 cell[x][y].walkability != UNWALKABLE ) 
				{
					corner = WALKABLE;	

					// sprawdzanie naroznikow
					if (x == thisPoint.x-1) 
					{
						if (y == thisPoint.y-1)
						{
							if (cell[thisPoint.x-1][thisPoint.y].walkability == UNWALKABLE
								|| cell[thisPoint.x][thisPoint.y-1].walkability == UNWALKABLE) 
								corner = UNWALKABLE;
						}
						else if (y == thisPoint.y+1)
						{
							if (cell[thisPoint.x][thisPoint.y+1].walkability == UNWALKABLE
								|| cell[thisPoint.x-1][thisPoint.y].walkability == UNWALKABLE) 
								corner = UNWALKABLE; 
						}
					}
					else if (x == thisPoint.x+1)
					{
						if (y == thisPoint.y-1)
						{
							if (cell[thisPoint.x][thisPoint.y-1].walkability == UNWALKABLE 
								|| cell[thisPoint.x+1][thisPoint.y].walkability == UNWALKABLE) 
								corner = UNWALKABLE;
						}
						else if (y == thisPoint.y+1)
						{
							if (cell[thisPoint.x+1][thisPoint.y].walkability == UNWALKABLE 
								|| cell[thisPoint.x][thisPoint.y+1].walkability == UNWALKABLE)
								corner = UNWALKABLE; 
						}
					}	
				
					if( corner == WALKABLE ){

					if ( cell[x][y].whichList != openListMarker ) 
					{
						cell[x][y].whichList = openListMarker;
						cell[x][y].parent = thisPoint;

						//liczenie kosztu G
						if ( abs( x - thisPoint.x ) == 1 && abs( y - thisPoint.y ) == 1 )
						addedGCost = 14;//po skosie
						else	
						addedGCost = 10;//po krzyzu	

						cell[x][y].GCost = cell[thisPoint.x][thisPoint.y].GCost + addedGCost;
					
						//liczenie kosztu H
						cell[x][y].HCost = 10 * ( abs(x - target.x) + abs(y - target.y) );
						//liczenie kosztu F
						cell[x][y].FCost = cell[x][y].GCost + cell[x][y].HCost;

						openList->AddPointToList( sf::Vector2i(x,y),cell[x][y].FCost ); //nie przekazuje kosztu H
						//liczenie F,G,H
					}else //jesli jest juz na otwartej liscie
					{
						int tempGcost = 0;
						//liczenie kosztu G tej mozliwie lepszej sciezki
						if ( abs( x-thisPoint.x ) == 1 && abs( y - thisPoint.y ) == 1)
							addedGCost = 14;//po skosie
						else	
							addedGCost = 10;//po krzyzu				
						tempGcost = cell[thisPoint.x][thisPoint.y].GCost + addedGCost;

						if ( tempGcost < cell[x][y].GCost ) 
						{
							cell[x][y].parent = thisPoint;
							cell[x][y].GCost  = tempGcost;	
							cell[x][y].FCost = cell[x][y].GCost + cell[x][y].HCost;						
							openList->AddNewFCostAndSort( openList->GetPointID( sf::Vector2i( x , y ) ) , cell[x][y].FCost );
						}

					}
					}
				}
			}
		}
	}

}
int PathFinder::SaveFoundedPath(int pathfinderID , sf::Vector2i starting )
{
	sf::Vector2i tempCell = target;
	sf::Vector2i oldTempCell = tempCell;
	pathLength[pathfinderID] = 0;

	do{
		oldTempCell = tempCell;
		tempCell = cell[tempCell.x][tempCell.y].parent;	
		if( cell[tempCell.x][tempCell.y].parent == oldTempCell )
		{
			std::cout<<"Path Corrupted ! \n";
			return NONEXISTENT;
		}
		pathLength[pathfinderID]++;
	}while( tempCell != starting );
	
	pathBank[pathfinderID] = new sf::Vector2i[ pathLength[pathfinderID] ];
	
	tempCell = target;
	int iterator = pathLength[pathfinderID] - 1;

	//std::cout<<"pathLength["<<pathfinderID<<"] = "<<pathLength[pathfinderID]<<std::endl;
	do{
		pathBank[pathfinderID][ iterator ] = tempCell;
		tempCell = cell[tempCell.x][tempCell.y].parent;	
		iterator--;
	}while( tempCell != starting );

	return FOUND;


}
void PathFinder::SetNumberOfMobs( int _numberOfMobs )
{
	numberOfMobs = _numberOfMobs;
	for( int i = 0 ; i< numberOfMobs ; i++ )
	{
		pathStatus.push_back(-1);
		pathLength.push_back(-1);
		foundedCoords.push_back( sf::Vector2i(0,0) );
	}
	pathBank = new sf::Vector2i*[numberOfMobs];

}
std::vector<sf::Vector2i> PathFinder::GetPath(int pathfinderID )
{
	std::vector<sf::Vector2i> vectorPath;
	for( int i = 0 ; i < pathLength[pathfinderID] ; i++ )
	{
		vectorPath.push_back(sf::Vector2i ( pathBank[pathfinderID][i].x , pathBank[pathfinderID][i].y ) ); // y x
	}
	return vectorPath;

}
int PathFinder::AddNewMobID()
{
	int _numberOfMobs = numberOfMobs;
	pathStatus.push_back(numberOfMobs);
	pathLength.push_back(numberOfMobs);
	foundedCoords.push_back(sf::Vector2i(0,0));
	pathBank = new sf::Vector2i*[numberOfMobs];
	numberOfMobs++;
	return _numberOfMobs;

}
bool PathFinder::IsInSight( sf::Vector2i _start, sf::Vector2i _target)
{
	bool obsticle          = false;
	int walkabilityCounter = 0;
	
	sf::Vector2i start    = sf::Vector2i( _start.x  / gridCellSize, _start.y  / gridCellSize );
	sf::Vector2i target   = sf::Vector2i( _target.x / gridCellSize, _target.y / gridCellSize );
	sf::Vector2i tempPos  = start;

	do{
		if( target.x > tempPos.x ) 
		{
			tempPos.x++;
		}else if(target.x < tempPos.x )
		{
			tempPos.x--;
		}
		if( target.y > tempPos.y )
		{
			tempPos.y++;
		}else if( target.y < tempPos.y )
		{
			tempPos.y--;
		}
		if(cell[tempPos.x][tempPos.y].walkability != WALKABLE )
		{
			obsticle = true;
		}
		if( obsticle )
		{
			return false;
		}
	}while( tempPos != target );
		return true;
}