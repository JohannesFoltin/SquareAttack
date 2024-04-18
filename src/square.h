#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>



class Square
{
public:
	const sf::Sprite& sprite;
	Square(int speed,sf::Vector2f startPoint,sf::Vector2f direction,sf::Vector2f dimensions);
	~Square();
	sf::Sprite update(float delta);
	void reset();
	void gameOver();


private:
	sf::Vector2f normelizeVector(sf::Vector2f vector);
	sf::Vector2f _dimensions;
	sf::Texture _texture;
	sf::Vector2f _direction;
	int _speed;
	sf::Sprite _sprite;
};
