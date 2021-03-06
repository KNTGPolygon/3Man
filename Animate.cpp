#include "Animate.h"

Animate::Animate(std::string filePath,sf::Vector2i FrameSize,sf::Vector2f Position,int NumberOfFrames,int FrameRate,sf::Vector2i Shift )
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
			mySprite[i].SetSubRect(sf::IntRect((i+Shift.x)*FrameSize.x,Shift.y*FrameSize.y,FrameSize.x + (i+Shift.x)*FrameSize.x,Shift.y*FrameSize.y+FrameSize.y));
			mySprite[i].SetPosition(Position);
			mySprite[i].SetCenter(18,25);

		}
}

Animate::~Animate(void)
{
	delete[] mySprite;
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
