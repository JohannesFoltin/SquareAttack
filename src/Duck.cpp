#include "Duck.h"
#include <iostream>

Duck::Duck(int speed,sf::Vector2u screen):sprite(_sprite)
{
	this->_speed = speed;
	this->_screenSize = screen;
	this->_angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 180));
    sf::Texture texture;
    if (!texture.loadFromFile("textures/Duck.png"))
    {
        std::cout << "Error";
    }

    sf::Sprite sprite;

    sprite.setTexture(texture);
    
    sprite.setScale(0.2, 0.2);
    sprite.setRotation(_angle);
    sprite.setPosition(sf::Vector2f(10.f, 50.f));
}

Duck::~Duck()
{
}

void Duck::start()
{
}

void Duck::update(float delta)
{
}

void Duck::kill()
{
}

void Duck::flyAway()
{
}

bool Duck::collisionCheck()
{
	return false;
}
