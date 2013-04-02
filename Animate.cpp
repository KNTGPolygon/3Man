#include "Animate.h"

Animate::Animate(std::string filePath,sf::Vector2i FrameSize,sf::Vector2f Position,int NumberOfFrames,int FrameRate,int Shift )
:frameRate(FrameRate),numberOfFrames(NumberOfFrames)
{
		time.Reset();
		frameNumber = 0;
		myTexture = ImageManager::getInstance()->loadImage( filePath );
		myTexture.CreateMaskFromColor(sf::Color(255,0,255));
		myTexture.SetSmooth(false);

		mySprite = new sf::Sprite[NumberOfFrames];

		for(int i = 0 ; i < NumberOfFrames ; i++)
		{
		mySprite[i].SetImage(myTexture);
		mySprite[i].SetSubRect(sf::IntRect(i*FrameSize.x,Shift*FrameSize.y,FrameSize.x + i*FrameSize.x,Shift*FrameSize.y+FrameSize.y));
		mySprite[i].SetPosition(Position);
		}
}

Animate::~Animate(void)
{
	delete[] mySprite;
	myTexture.~Image();
}
void Animate::Update(sf::Vector2f Position)
{
	for(int i = 0 ; i <numberOfFrames ; i++)
		{
		mySprite[i].SetPosition(Position);
		}
}
void Animate::Display(sf::RenderWindow *window)
{
	window->Draw(mySprite[frameNumber]);
	if(window->GetFrameTime()*(float)frameRate <time.GetElapsedTime())
	{
		time.Reset();		
		frameNumber++;
		if(frameNumber>(numberOfFrames-1))
		frameNumber = 0;
	}
}