#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

int ground = 400;

const int Hight = 24;
const int Width = 40;

String TileMap[Hight]= 
{

"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                           W          W",
"W                                      W",
"W                                      W",
"W                           W          W",
"W         0000           WWWW          W",
"W         WWWW           WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W                        WWWW          W",
"W           000             W          W",
"W           WWW             W          W",
"W    00000                  W          W",
"W    WWWWW               WWWW          W",
"W                                      W",
"W                                      W",
"W                                      W",
"WWWWWWWW    WWWWWWWWWWWWWWWWWWWWWWWWWWWW",

};

class PLAYER 
{	
	public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
		 PLAYER(Texture &image)
		 {
			 sprite.setTexture(image);
			 rect = FloatRect(128,128,128,128);
			 dx=dy=0;
			 currentFrame = 0;
		 }
	
	void update(float time)
	{
		rect.left += dx * time;
		if(!onGround) dy=dy + 0.0005*time;
		rect.top += dy * time;
		onGround = false;
		if (rect.top > ground)
		{
			rect.top = ground; 
			dy = 0;
			onGround = true;
		}

		currentFrame += 0.005*time;
		if (currentFrame>9) currentFrame -=9;

		if (dx<0)	sprite.setTextureRect(IntRect(128*int(currentFrame)+128,256,-128,128));
		if (dx>0)	sprite.setTextureRect(IntRect(128*int(currentFrame),256,128,128));	
		sprite.setPosition(rect.left, rect.top);
		dx=0;
	}
};

int main() 
{ 
    RenderWindow window(VideoMode(1600,800), "Test");
	
	Texture t;
	t.loadFromFile("dinasor.jpg");

	float currentFrame=0;

	PLAYER p(t);

	Clock clock;

	RectangleShape rectangle;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		 
		time = time/800;

		Event event;
		while (window.pollEvent(event))
		
		{
		if (event.type == Event::Closed)
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.4;
			
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.4;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround)
			{
				p.dy=-0.4;
				p.onGround=false;
			}
			
		}

		p.update(time);
		window.clear(Color::Black);

		
		for (int i=0; i<Hight; i++)
			for (int j=0; j<Width; j++)
				{
					if (TileMap[i][j] == 'W') rectangle.setFillColor(Color::Yellow);
					if (TileMap[i][j] == '0') rectangle.setFillColor(Color::Green);
					if (TileMap[i][j] == ' ') continue;

					rectangle.setPosition(j*32,i*32);
					rectangle.setSize(sf::Vector2f(32,32));
					window.draw(rectangle);
				}
		window.draw(p.sprite);
		window.display();
	}
    return 0; 
}

