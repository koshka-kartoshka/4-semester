#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main() 
{ 
    RenderWindow window(VideoMode(800,1600), "Test");
	CircleShape MyCircle(100.f);
	MyCircle.setFillColor(Color::Green);

	Texture t;
	t.loadFromFile("dinasor.jpg");

	float currentFrame=0;

	Sprite s;
	s.setTexture(t);
	s.setTextureRect(IntRect(0,256,128,128));
	s.setPosition(50,100);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
		if (event.type == Event::Closed)
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			s.move(-0.1,0);

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			s.move(0.1,0);

			currentFrame += 0.006;
			if (currentFrame>9) currentFrame -=9;

			s.setTextureRect(IntRect(128*int(currentFrame),256,128,128));

		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			s.move(0,-0.1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			s.move(0,0.1);
		}


		window.clear();
		window.draw(s);
		window.display();

	}

    return 0; 
}