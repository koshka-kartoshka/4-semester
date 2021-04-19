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
const int Width = 400;	 ;

String TileMap[Hight]= 
{

"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                               W                                                                  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW      W",
"W                                                                                          WWWWWWWWWWWWWWWWWWWWWWWWWW      W",
"W                                                                                                  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W",
"W                               W                                                                                                  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW          W",
"W         0000               WWWW                                                                                                 WWWWWWWWWWWWWWWWWWWWWWWWWW                         W",
"W         WWWW                                                                                                        WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W",
"W                                                                                                                           WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW     W",
"W                                                       000000000000000000     000000000000000000000                                                                   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W",
"W                        WWWW                           000000000000000000     000000000000000000000                                                                          WWWWWWWWWWWWWWWWWWWWW    W",
"W                    WWWWW                              000000000000000                                                                              WWWWWWWWWWWWWWWWWW   W",
"W             WWWWWWWW                                 WWWWWWWWWWW                                                                     WWWWWWWWWWWWWWWWWWWWWWWWW   ",
"W              WWW                        WWWWWWWWWWWWW           WWWWWWWWWWWWWW                                                        WWWWWWWWWWWWWWWWWWWWWWWWW   ",
"W                                        WWWWW  W                              WWWWWWWWWWWW                                                                                ",
"W                                   WWWWW       W                                                WWWWWWW      WWWWWWWWWWWWWW                       WWWWWWWWWWWWWWWWWWWWWW  WWWWWWWWWWWWW",
"W                               WWWW                                                                                  WWWWWWWWWWWWWWWWWWWWWWWW                                        WWWWWWWWWWW ",
"W                             WWWW                                                                                                                 WWWWWWWWWWWWWWWWWWW",
"W    00000          0000 WWWW                                                                                                WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW             W",
"W                     WWWW                                                                                                                     WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                            W",
"W                                                                                                                                        WWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W",
"W                                                                                                                                     WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW     W",
"W                                                                                                                                      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", 

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
		sprite.setTextureRect(IntRect(0,0,165,172));
		sprite.setPosition(rect.left - ofSetX, rect.top - ofSetY);
		
	}
	
	void Collision()
  {
    for (int i = rect.top/32  ; i < (rect.top + rect.height)/32 ; i++)
    for (int j = rect.left/32 ; j < (rect.left + rect.width)/32 ; j++)
	 {
      if ((TileMap[i][j]=='W') || (TileMap[i][j]=='0'))
	   {
        if (dx > 0)      
			{ 
			rect.left = j*32 - rect.width;
			dx *= -1;
			 }
        else if (dx < 0) 
		{
		 //sprite.setTextureRect(IntRect(180,180,-180,180));
		 sprite.setPosition(rect.left - ofSetX, rect.top - ofSetY);
		 rect.left = j*32 + 32;
         dx *= -1; }
        }
      }
    }
	
		
};


int main() 
{ 
    RenderWindow window(VideoMode(1600,800), "Test");
	
	Texture t;
	Texture evel;
	Texture texture;
	t.loadFromFile("Background.png");
	evel.loadFromFile("donat.png");
	texture.loadFromFile("tail.png");
	Sprite wall(texture);

	float currentFrame=0;

	PLAYER p(t);
	ENEMY enemy1;
	ENEMY enemy2;
	enemy1.set(evel,1500,500);
	enemy2.set(evel,2200,500);

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
		enemy1.update(time);
		enemy2.update(time);


		if (p.rect.intersects(enemy1.rect))
		{
			enemy1.life=false;
			std::cout<<"Game over";
			window.close();
		}

		if (p.rect.intersects(enemy2.rect))
		{
			enemy2.life=false;
			std::cout<<"Game over";
			window.close();
		}

		if (p.rect.left>800) ofSetX=p.rect.left - 1600/2;
		ofSetY=p.rect.top - 800/2;

		window.clear(Color::Black);

		
		for (int i=0; i<Hight; i++)
			for (int j=0; j<Width; j++)
				{
					if (TileMap[i][j] == 'W')
					{
						wall.setTextureRect(IntRect(200,100,32,32));
					}
					if (TileMap[i][j] == '0') 
					{
						wall.setTextureRect(IntRect(700,100,32,32));
					}
					if (TileMap[i][j] == ' ') continue;

					wall.setPosition(j*32 - ofSetX,i*32- ofSetY);
					window.draw(wall);
				}
		window.draw(p.sprite);
		window.draw(enemy1.sprite);
		window.draw(enemy2.sprite);
		window.display();
	}
    return 0; 
}

