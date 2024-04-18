#include "square.h"

# define M_PI           3.14159265358979323846  /* pi */

Square::Square(int speed, sf::Vector2f startPoint, sf::Vector2f direction, sf::Vector2f dimensions):sprite(_sprite)
{
	this->_speed = speed;
    this->_dimensions = dimensions;

    this->_direction = normelizeVector(direction);

    sf::Texture texture;

    if (!texture.loadFromFile("textures/Square.png"))
    {
        std::cout << "Error";
    }
    this->_texture = texture;

    sf::Sprite sprite;
    
    sprite.setTexture(this->_texture);


    sprite.setPosition(startPoint);


    this->_sprite = sprite;
   
}

Square::~Square()
{
}

sf::Sprite Square::update(float delta)
{
    sf::Vector2f spritePosition = this->_sprite.getPosition();
    sf::Vector2f dimensions = this->_dimensions;

    if (spritePosition.x < 0 || (spritePosition.x+this->_texture.getSize().x)> dimensions.x) {

        // Kollisionsbehandlung f�r X-Richtung: Abprallen von der Wand
        double normalX = 0.0; 
        double normalY = (spritePosition.x < 0) ? 1.0 : -1.0;

        // Berechne den Winkel zwischen dem aktuellen Richtungsvektor und der Normalen
        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        // Berechne den reflektierten Winkel (Einfallswinkel = Ausfallswinkel)
        double reflectedAngle = 2 * angle - incidentAngle;

        // Berechne den neuen Richtungsvektor basierend auf dem reflektierten Winkel
        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);

        this->_direction = normelizeVector(this->_direction);
        
    }

    if (spritePosition.y < 0 || (spritePosition.y + this->_texture.getSize().y) > dimensions.y) {
        // Kollisionsbehandlung f�r Y-Richtung: Umkehren der Richtung
        double normalX = (spritePosition.y < 0) ? 1.0 : -1.0; 
        double normalY = 0.0; 

        // Berechne den Winkel zwischen dem aktuellen Richtungsvektor und der Normalen
        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        // Berechne den reflektierten Winkel (Einfallswinkel = Ausfallswinkel)
        double reflectedAngle = 2 * angle - incidentAngle;

        // Berechne den neuen Richtungsvektor basierend auf dem reflektierten Winkel
        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);

        this->_direction = normelizeVector(this->_direction);
        
    }

    this->_sprite.move(this->_speed * delta* _direction.x, this->_speed * delta * _direction.y);
    return this->_sprite;
}

void Square::reset()
{

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distributionX(100, (this->_dimensions.x -100));
    std::uniform_int_distribution<int> distributionY(100, (this->_dimensions.y -100));

    this->_sprite.setPosition(sf::Vector2f(distributionX(gen), distributionY(gen)));

    std::uniform_int_distribution<int> distributionXd(-100, 100);
    std::uniform_int_distribution<int> distributionYd(-100, 100);

    this->_direction = normelizeVector(sf::Vector2f(distributionXd(gen), distributionYd(gen)));

    this->_speed = this->_speed + 5;
}


sf::Vector2f Square::normelizeVector(sf::Vector2f vector) {
    double vectorLength = sqrt(vector.x * vector.x + vector.y * vector.y);
    return sf::Vector2f(vector.x / vectorLength, vector.y / vectorLength);
};