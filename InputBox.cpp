#include "InputBox.h"
#include "GameEngine.h"

InputBox::InputBox(const sf::Input &_steering,sf::Vector2f _position, std::string defaultInboxText, sf::Vector2f _size):
position(_position), size(_size), steering(_steering)
{
	textSize = 20.0;
	box		= sf::Shape::Rectangle(0,0,size.x,size.y,sf::Color(125,125,125));
	karetka = sf::Shape::Rectangle(0,0,2.0,textSize + 4,sf::Color(0,0,0));
	text.SetColor(sf::Color(0,0,0));
	textString = defaultInboxText;
	tempTextString = textString;
	text.SetText(textString);
	text.SetSize(textSize);
	box.SetPosition(position);
	text.SetPosition(position.x + TEXT_SHIFT,position.y + 5 );
	karetka.SetPosition(position.x + TEXT_SHIFT,position.y + 3 );
	karetkaVisable  = false;
	typing			= false;
	keyHolded		= false;
	singleKeyPress  = false;
	lastTime = currentTime = 0.0;
	karetkaBlinkTime = 0.5;
	lastSymbolEntered = 0;
	stringShift = 0;
}

InputBox::~InputBox(void)
{
}
void InputBox::HandleEvent(sf::Event event)
{
	if(  ( (GameEngine::getInstance()->GetMouseCoords().x) < ( size.x + position.x) && (GameEngine::getInstance()->GetMouseCoords().x) > (position.x) )
	  && ( (GameEngine::getInstance()->GetMouseCoords().y) < ( size.y + position.y) && (GameEngine::getInstance()->GetMouseCoords().y) > (position.y) ))
	{
		if(steering.IsMouseButtonDown(sf::Mouse::Left))
		{
			box.SetColor(sf::Color(255,255,255));
	
		active = true;
		karetkaVisable = true;
		}
	}
	else
	{
		if(steering.IsMouseButtonDown(sf::Mouse::Left))
		{
		box.SetColor(sf::Color(125,125,125));
		active = false;
		karetkaVisable = false;
		}
	}
	if(active == true)
	{
		currentTime = timer.GetElapsedTime();
			
		if(event.Type == sf::Event::TextEntered)		
		{	
			typing = true;

			
			
			
			// wcisnieto raz 
			if(event.Text.Unicode == lastSymbolEntered && singleKeyPress == false)
			{
				if(event.Text.Unicode == 8 && textString.  length()>0 )
				{
					textString.erase( textString.length() - 1 );
					lastSymbolEntered = event.Text.Unicode;
					lastTime = currentTime;	
					if( stringShift > 0 ) stringShift--;
				}

				else if(event.Text.Unicode != 8 )
				{
					lastSymbolEntered = event.Text.Unicode;
					lastTime = currentTime;	
					textString += (char)event.Text.Unicode;
				}
			}
			//przytrzymano

			else if(event.Text.Unicode == lastSymbolEntered && singleKeyPress == true)
			{
				if( (currentTime - lastTime) > 0.5  )
				{
						keyHolded = true;
						lastTime = currentTime;
				}

				if( keyHolded == true )
				{
					if(event.Text.Unicode == 8 && textString.length()>0 
					 && (currentTime-lastTime)>0.05 )
					{
						textString.erase( textString.length() - 1 );
						lastSymbolEntered = event.Text.Unicode;
						lastTime = currentTime;	
						if( stringShift > 0 ) stringShift--;
					}

					else
					if((currentTime-lastTime)>0.05 && event.Text.Unicode != 8 )
					{
						lastSymbolEntered = event.Text.Unicode;
						lastTime = currentTime;	
						textString += (char)event.Text.Unicode;
					}
				}
			}

			//wcisnieto inny klawisz
			if( event.Text.Unicode != lastSymbolEntered)
			{
				if(event.Text.Unicode == 8 && textString.length()>0)
				{
					textString.erase( textString.length() - 1 );
					if( stringShift > 0 ) stringShift--;
				}else if(event.Text.Unicode != 8 )
				{
				textString += (char)event.Text.Unicode;
				}
				
				lastTime = currentTime;
				lastSymbolEntered = event.Text.Unicode;
				
				
			}
			singleKeyPress = true;		
		}
		else 
			{
				typing		   = false;
				singleKeyPress = false;
				keyHolded      = false;
			}
		
		text.SetText( tempTextString );
		karetka.SetPosition(text.GetPosition().x + text.GetRect().GetWidth() ,position.y + 3);
		
		tempTextString = textString.substr( stringShift,tempTextString.length() + 1 );

		if(karetka.GetPosition().x > ( box.GetPosition().x + size.x - TEXT_SHIFT ) )
		{
			stringShift += 1;
		}	
		
	}
}
void InputBox::Display(sf::RenderWindow *window)
{
	window->Draw( box );
	window->Draw( text );
	if( karetkaVisable == true )
	{
		if( typing )
		{
			window->Draw( karetka );
		}
		else
		{
			if( karetkaBlinkTime < karetkaTime.GetElapsedTime() )
			{
			window->Draw( karetka );
			}
			if(karetkaBlinkTime*2 < karetkaTime.GetElapsedTime())
				karetkaTime.Reset();
		}
	}
}
std::string InputBox::GetString()
{
	return textString;
}
void InputBox::SetFontSize(int Size)
{
	text.SetSize( (float) Size );
	karetka.Rectangle(0,0,2.0,(float) Size + 4,sf::Color(0,0,0));
}
