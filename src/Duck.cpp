#include "Duck.h"
#include <iostream>

Duck::Duck(int speed, sf::Vector2f startPoint, sf::Vector2f direction):sprite(_sprite)
{
	this->_speed = speed;
    this->_direction = direction;

    this->_angle = 0.3;

    sf::Texture texture;
    if (!texture.loadFromFile("textures/Duck.png"))
    {
        std::cout << "Error";
    }

    sf::Sprite sprite;

    sprite.setTexture(texture);
    
    sprite.setScale(0.2, 0.2);

    sprite.setPosition(startPoint);

    this->_sprite = sprite;
   
}

Duck::~Duck()
{
}

void Duck::start()
{
}

sf::Sprite Duck::update(float delta)
{
    this->_sprite.move(this->_speed * delta, 0.f);
    return this->_sprite;

}

void Duck::wallCollsion(sf::Vector2f newDirection)
{
}

void Duck::kill()
{
}

void Duck::flyAway()
{
}

