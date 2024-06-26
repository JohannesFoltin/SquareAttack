#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>


// Definition of the Square Class
class Square
{
public:
	const sf::Sprite& sprite;
	Square(int speed,sf::Vector2f dimensions);
	~Square();
	sf::Sprite update(float delta);
	void reset();
	void increaseSpeed(int value);
	void resetSpeed(int newValue);
	void gameOver();


private:
	sf::Vector2f _dimensions;
	sf::Texture _texture;
	sf::Vector2f _direction;
	int _speed;
	sf::Sprite _sprite;
	sf::Vector2f calculateStartPoint();
	sf::Vector2f normelizeVector(sf::Vector2f vector);
};
