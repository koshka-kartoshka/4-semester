#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

int ground = 256;

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
			p.dx = -0.1;
			
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
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
		window.draw(p.sprite);
		window.display();
	}
    return 0; 
}

