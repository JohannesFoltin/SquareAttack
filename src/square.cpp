#include "square.h"

# define M_PI           3.14159265358979323846  /* pi */

// Implementaion of the Square Class
Square::Square(int speed, sf::Vector2f dimensions):sprite(_sprite)
{
	this->_speed = speed;

    this->_dimensions = dimensions;


    // Load the square Texture
    sf::Texture texture;

    if (!texture.loadFromFile("textures/Square.png"))
    {
        std::cout << "Error";
    }

    this->_texture = texture;

    sf::Sprite sprite;
    
    sprite.setTexture(this->_texture);
    
    // To initialise a random direction. The Position will be overritten later
    reset();

    // Set the start Position
    sprite.setPosition(calculateStartPoint());

    this->_sprite = sprite;
   
}

Square::~Square()
{
}

sf::Sprite Square::update(float delta)
{
    sf::Vector2f spritePosition = this->_sprite.getPosition();
    sf::Vector2f dimensions = this->_dimensions;

    // Collision handling with the x Wall
    if (spritePosition.x < 0 || (spritePosition.x+this->_texture.getSize().x)> dimensions.x) {

        // Angle calculation
        double normalX = 0.0; 
        double normalY = (spritePosition.x < 0) ? 1.0 : -1.0;

        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        double reflectedAngle = 2 * angle - incidentAngle;

        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);

        this->_direction = normelizeVector(this->_direction);
        
    }

    // Collision handling with the y Wall
    if (spritePosition.y < 0 || (spritePosition.y + this->_texture.getSize().y) > dimensions.y) {

        // Angle calculation
        double normalX = (spritePosition.y < 0) ? 1.0 : -1.0; 
        double normalY = 0.0; 

        double angle = atan2(normalY, normalX);
        double incidentAngle = atan2(this->_direction.y, this->_direction.x);

        double reflectedAngle = 2 * angle - incidentAngle;

        this->_direction.x = cos(reflectedAngle);
        this->_direction.y = sin(reflectedAngle);

        this->_direction = normelizeVector(this->_direction);
        
    }

    // Move the Sprite in the right direction and the right distance
    this->_sprite.move(this->_speed * delta* _direction.x, this->_speed * delta * _direction.y);
    return this->_sprite;
}

// Generate a random direction and position
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
}

void Square::increaseSpeed(int value)
{
    this->_speed = this->_speed + value;
}

void Square::resetSpeed(int newValue)
{
    this->_speed = newValue;
}

void Square::gameOver()
{
    // Reset the Sprite to the center
    this->_sprite.setPosition(calculateStartPoint());
}

// calculate the center of the screen
sf::Vector2f Square::calculateStartPoint()
{
    float startPointX = (this->_dimensions.x / 2) - this->_texture.getSize().x;
    float startPointY = (this->_dimensions.y / 2) - this->_texture.getSize().y;

    return sf::Vector2f(startPointX, startPointY);
}

// Normelize a vector
sf::Vector2f Square::normelizeVector(sf::Vector2f vector) {
    double vectorLength = sqrt(vector.x * vector.x + vector.y * vector.y);
    return sf::Vector2f(vector.x / vectorLength, vector.y / vectorLength);
};