#include <SFML/Graphics.hpp>


class Duck
{
public:
	const sf::Sprite& sprite;
	Duck(int speed,sf::Vector2u screen);
	~Duck();
	void start();
	void update(float delta);
	void kill();
	void flyAway();

private:
	float _angle;
	sf::Vector2u _screenSize;
	sf::Vector2i _goal;
	int _speed;
	sf::Sprite _sprite;

	bool collisionCheck();
};
