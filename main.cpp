#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

int ground = 400;
int n=0;

float ofSetX=0;
float ofSetY=0;

const int Hight = 30;
const int Width = 200;	 ;

String TileMap[Hight]= 
{

"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                               W                                                                        W",
"W                                                                                                W",
"W                                                                                                    W",
"W                               W                                                                                                            W",
"W         0000               WWWW                                                                                                                          W",
"W         WWWW                                                                                                          W",
"W                                                                                                                                W",
"W                                                                                                                                   W",
"W                        WWWW                                                                                                            W",
"W                    WWWWW                                                                                                               W",
"W             WWWWWWWW                                 WWWWWWWWWWW                                                                        ",
"W              WWW                        WWWWWWWWWWWWW           WWWWWWWWWWWWWW                                                           ",
"W                                        WWWWW  W                              WWWWWWWWWWWW                                               ",
"W                                   WWWWW       W                                                                            WWWWWWWWWWWWW",
"W                               WWWW       W                                                                                   WWWWWWWWWWW ",
"W                             WWWW               W                                                                      WWWWWWWWWWWWWWWWWWW",
"W    00000          0000 WWWW                                                                                                             W",
"W                     WWWW                           WWWW                                                                                 W",
"W                                                                                                                                          W",
"W                                                                                                                                          W",
"W                                                                                                                                          W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", 

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

		Collision(0);

		if(!onGround) dy=dy + 0.0005*time;
		rect.top += dy * time;
		onGround = false;

		Collision(1);
		

		/*if (rect.top > ground)
		{
			rect.top = ground; 
			dy = 0;
			onGround = true;
		}*/

		currentFrame += 0.005*time;
		if (currentFrame>9) currentFrame -=9;

		if (dx<0)	sprite.setTextureRect(IntRect(128*int(currentFrame)+128,256,-128,128));
		if (dx>0)	sprite.setTextureRect(IntRect(128*int(currentFrame),256,128,128));	
		sprite.setPosition(rect.left - ofSetX, rect.top - ofSetY);
		dx=0;
	}
	


	void Collision(int dic)
	{
		for (int i=rect.top/32; i<(rect.top+rect.height)/32; i++)
			for (int j=rect.left/32; j<(rect.left+rect.width)/32; j++)
			{
			if (TileMap[i][j]=='W')
				{
					if ((dx>0) && (dic == 0)) rect.left = j*32 - rect.width;
					if ((dx<0) && (dic == 0)) rect.left = j*32 + 32; 
					if ((dy>0) && (dic == 1)) {rect.top = i*32 - rect.height; dy=0; onGround=true;}
					if ((dy<0) && (dic == 1))   {rect.top = i*32+32; dy=0; }
				}
				if(TileMap[i][j]=='0')
				{
					TileMap[i][j]=' ';
				}
			}	

	}


};

class ENEMY
{
public:
float dx, dy;
FloatRect rect;
Sprite sprite;
float currentFrame;
bool life;
/*ENEMY(Texture &image)
		 {
			 sprite.setTexture(image);
			 rect = FloatRect(300,300,128,128);
			 dx=dy=0;
			 currentFrame = 0;
		 }*/


	
	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect=FloatRect(x,y,180,180);
		dx=0.05;
		currentFrame=0;
		life=true;
	}
	void update(float time)
	{ 
		rect.left += dx*time;
		Collision();
		currentFrame+=time * 0.005;
		if (currentFrame>2) currentFrame-=2;
		sprite.setTextureRect(IntRect(180*int(currentFrame),0,180,180));
		if (!life) sprite.setTextureRect(IntRect(720, 360, 180, 180));
		sprite.setPosition(rect.left - ofSetX, rect.top - ofSetY);

	}
	
	void Collision()
  {
    for (int i = rect.top/32  ; i < (rect.top + rect.height)/32 ; i++)
    for (int j = rect.left/32 ; j < (rect.left + rect.width)/32 ; j++)
	 {
      if ((TileMap[i][j]=='W') || (TileMap[i][j]=='0'))
	   {
        if (dx > 0)      { rect.left = j*32 - rect.width; dx *= -1; }
        if (dx < 0) { rect.left = j*32 + 32;         dx *= -1; }
      }
    }
  }
		
};


int main() 
{ 
    RenderWindow window(VideoMode(1600,800), "Test");
	
	Texture t;
	Texture evel;
	t.loadFromFile("Background.png");
	evel.loadFromFile("vonkey.jpg");

	float currentFrame=0;

	PLAYER p(t);
	ENEMY enemy;
	enemy.set(evel,2000,500);

	Sprite tile(t);

	Clock clock;

	RectangleShape rectangle;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		 
		time = time/800;

		if (time > 20) time = 20;

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
		enemy.update(time);


		if (p.rect.intersects(enemy.rect))
		{
			p.sprite.setColor(Color::Red);
			//enemy.life=false;
		}

		if (p.rect.left>800) ofSetX=p.rect.left - 1600/2;
		ofSetY=p.rect.top - 800/2;

		window.clear(Color::Black);

		
		for (int i=0; i<Hight; i++)
			for (int j=0; j<Width; j++)
				{
					if (TileMap[i][j] == 'W') rectangle.setFillColor(Color::Yellow);
					if (TileMap[i][j] == '0') rectangle.setFillColor(Color::Green);
					if (TileMap[i][j] == ' ') continue;

					rectangle.setPosition(j*32 - ofSetX,i*32- ofSetY);
					rectangle.setSize(sf::Vector2f(32,32));
					window.draw(rectangle);
				}
		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
    return 0; 
}

