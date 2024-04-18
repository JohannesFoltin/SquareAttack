#include "Duck.h"

Duck::Duck(int speed, sf::Vector2f startPoint, sf::Vector2f direction, sf::Vector2f dimensions):sprite(_sprite)
{
	this->_speed = speed;
    this->_dimensions = dimensions;
    this->_direction = direction;

    sf::Texture texture;

    if (!texture.loadFromFile("textures/DuckSmall.png"))
    {
        std::cout << "Error";
    }

    this->_texture = texture;

    sf::Sprite sprite;
    
    sprite.setTexture(this->_texture);
    
    sprite.setPosition(startPoint);

    this->_sprite = sprite;

    float angle = sin(direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2))));

    std::cout << angle << "\n";
   
}

Duck::~Duck()
{
}

void Duck::start()
{
}

sf::Sprite Duck::update(float delta)
{
    sf::Vector2f spritePosition = this->_sprite.getPosition();
    sf::Vector2f dimensions = this->_dimensions;

    if (spritePosition.x < 0 || (spritePosition.x+this->_texture.getSize().x)> dimensions.x) {

        // Kollisionsbehandlung für X-Richtung: Abprallen von der Wand
        double normalX = 0.0; // Normale der Wand in X-Richtung
        double normalY = (spritePosition.x < 0) ? 1.0 : -1.0; // Normale der Wand in Y-Richtung

        // Berechne den Winkel zwischen dem aktuellen Richtungsvektor und der Normalen
        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        // Berechne den reflektierten Winkel (Einfallswinkel = Ausfallswinkel)
        double reflectedAngle = 2 * angle - incidentAngle;

        // Berechne den neuen Richtungsvektor basierend auf dem reflektierten Winkel
        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);
    }

    if (spritePosition.y < 0 || (spritePosition.y + this->_texture.getSize().y) > dimensions.y) {
        // Kollisionsbehandlung für Y-Richtung: Umkehren der Richtung
        double normalX = (spritePosition.y < 0) ? 1.0 : -1.0; // Normale der Wand in X-Richtung
        double normalY = 0.0; // Normale der Wand in Y-Richtung

        // Berechne den Winkel zwischen dem aktuellen Richtungsvektor und der Normalen
        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        // Berechne den reflektierten Winkel (Einfallswinkel = Ausfallswinkel)
        double reflectedAngle = 2 * angle - incidentAngle;

        // Berechne den neuen Richtungsvektor basierend auf dem reflektierten Winkel
        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);
    }

    this->_sprite.move((this->_speed * delta)* _direction.x, (this->_speed * delta) * _direction.y);
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

