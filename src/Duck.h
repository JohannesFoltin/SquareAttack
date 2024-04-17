#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>



class Duck
{
public:
	const sf::Sprite& sprite;
	Duck(int speed,sf::Vector2f startPoint,sf::Vector2f direction);
	~Duck();
	void start();
	sf::Sprite update(float delta);
	void wallCollsion(sf::Vector2f newDirection);
	void kill();
	void flyAway();

private:
	sf::Texture _texture;
	float _angle;
	sf::Vector2f _direction;
	int _speed;
	sf::Sprite _sprite;
};
