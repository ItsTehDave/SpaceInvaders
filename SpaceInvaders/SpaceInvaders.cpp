#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet : public sf::RectangleShape
{
public:
	sf::Vector2f m_speed;
	float BulletSpeed;
	bool dead = true;
	

	Bullet()
	{

	}
	Bullet(float x, float y)
	{
		setSize(sf::Vector2f(5, 5));
		setFillColor(sf::Color::Green);
		setPosition(sf::Vector2f(x, y));
		m_speed = sf::Vector2f(0, -3);
		dead = true;
	}

	void update()
	{
		setPosition(getPosition() + m_speed);
		if (getPosition().y < 0)
		{
			dead = true;
		}
	}
	void shoot(sf::Vector2f pos)
	{
		setPosition(pos);
		dead = false;
	}

	
};

class Player : public sf::RectangleShape
{
public:
	float playerx;
	float playery;
	float playerSpeed;
	bool PlayerDeath = false;
	int lives = 3;

	Player()
	{
	
	}

	void playerDeath()
	{
		if (PlayerDeath == true)
		{
			lives--;
			std::cout << "Lives: " << lives << std::endl;
		}

	}

};

class Enemy : public sf::RectangleShape
{

public:
	float Enemyx;
	float Enemyy;
	float EnemySpeed;
	bool dead = false;
	Enemy()
	{

	}

	Enemy(float x, float y)
	{
		setSize(sf::Vector2f(15, 15));
		setFillColor(sf::Color::Blue);
		Enemyx = x;
		Enemyy = y;
		EnemySpeed = 1.0f;
		setPosition(Enemyx, Enemyy);

	}
};

int main()
{
	Enemy enemyobject[52];
	int x = 10;
	int y = 15;
	for (int i = 0; i < 52; i++)
	{
		if (x >= 325)
		{
			x = 10;
			y = y + 30;
		}


		enemyobject[i] = Enemy(x, y);
		x = x + 25;
	}

	Bullet bulletobject[50];
	int p = 0;
	int t = 0;
	for (int i = 0; i < 50; i++)
	{

		bulletobject[i] = Bullet(-9000, -9000);
	}

	bool moveRight = true;
	bool side = false;
	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "First Graphics in C++");
	Enemy e = Enemy(50, 50);
	Bullet b = Bullet(5, 5);
	// setup any shapes or variables.




	sf::RectangleShape leftRect(sf::Vector2f(5, 15));
	sf::RectangleShape rightRect(sf::Vector2f(5, 15));
	sf::RectangleShape player(sf::Vector2f(80, 50));

	/*sf::Texture texture;
	(texture.loadFromFile("ship.png"));
		

	sf::Sprite sprite;
	sprite.setTexture(texture);

	sprite.setPosition(400, 530);

	leftRect.setPosition(-10, 530);
	rightRect.setPosition(800, 530);*/


	float playerX = 400;
	float playerY = 530;
	float playerSpeed = 1.0f;

	int fireRate = 0;
	int fireRateMax = 20;

	player.setFillColor(sf::Color::Red);

	player.setPosition(playerX, playerY);


	// set timepeFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greate than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{

			// get keyboard input.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerX = playerX - playerSpeed;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerX = playerX + playerSpeed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireRate <= 0)
			{

				bool funcdone = false;
				for (int i = 0; i < 50; i++)
				{
					if (bulletobject[i].dead == true && funcdone == false)
					{
						bulletobject[i].shoot(sf::Vector2f(playerX + 38, playerY));
						funcdone = true;
						fireRate = fireRateMax;
					}
				}
				//std::cout << "Space";

			}

			if (fireRate > 0)
			{
				fireRate--;
			}

			// update any variables...



			player.setPosition(playerX, playerY);

			// clear the screen and draw all the shapes
			//enemy move
			if (moveRight)
			{
				//e.Enemyx = e.Enemyx + e.EnemySpeed;
				for (int i = 0; i < 52; i++)
				{
					Player playerclass;
					Enemy  enemyClass;
					if (player.getGlobalBounds().intersects(enemyobject[i].getGlobalBounds()) == true)
					{
						window.close();
					}

					enemyobject[i].Enemyx = enemyobject[i].Enemyx + enemyobject[i].EnemySpeed;
					if (enemyobject[i].Enemyx >= 785)
					{
						moveRight = false;
						side = true;
					}

				}
			}
			else
			{
				for (int i = 0; i < 52; i++)
				{
					enemyobject[i].Enemyx = enemyobject[i].Enemyx - enemyobject[i].EnemySpeed;
					if (enemyobject[i].Enemyx <= 1)
					{
						moveRight = true;
						side = true;
					}

				}
			}
			if (side)
			{
				for (int i = 0; i < 52; i++)
				{
					enemyobject[i].Enemyy = enemyobject[i].Enemyy + 52;
				}
				side = false;
			}
			//e.setPosition(e.Enemyx, e.Enemyy);
			window.clear();

			window.draw(player);
			window.draw(leftRect);
			window.draw(rightRect);

			if (player.getGlobalBounds().intersects(leftRect.getGlobalBounds()) == true)
			{
				playerX = 710;
			}
			if (player.getGlobalBounds().intersects(rightRect.getGlobalBounds()) == true)
			{
				playerX = 10;
			}

			for (int i = 0; i < 52; i++)
			{

				for (int z = 0; z < 50; z++)
				{
					if (enemyobject[i].getGlobalBounds().intersects(bulletobject[z].getGlobalBounds()) == true)
					{
						bulletobject[z].dead = true;
						bulletobject[z].setPosition(-5,-5);
						enemyobject[i].dead = true;
						enemyobject[i].Enemyy = -9000;

						
					}
				}
				float x = enemyobject[i].Enemyx;
				float y = enemyobject[i].Enemyy;
				enemyobject[i].setPosition(x, y);
				if (enemyobject[i].dead == false)
				{
					window.draw(enemyobject[i]);
				}
				
			}
			
			window.draw(b);
			for (int i = 0; i < 50; i++)
			{
				if (bulletobject[i].dead != true)
				{
					bulletobject[i].update();
					window.draw(bulletobject[i]);
				}
				
			}

			//window.draw(sprite);
			

			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
	
	return 0;
}