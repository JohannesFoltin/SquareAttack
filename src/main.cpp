#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>

int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "QuackAttack" };
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(144);

    // Our speed in pixels per second
    float speed = 100.f;

    // Our clock to time frames
    sf::Clock clock;

    sf::Texture crosshair;
    crosshair.loadFromFile("textures/Crosshair.png");
    
    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshair);
    crosshairSprite.setScale(0.125, 0.125);

    sf::Texture texture;
    if (!texture.loadFromFile("textures/Duck.png"))
    {
        std::cout << "Error";
    }

    sf::Sprite sprite;

    sprite.setTexture(texture);
    
    sprite.setScale(0.2,0.2);

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();


        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(250,250,250));

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        if (localPosition.x < 0 || localPosition.y < 0)
        {
        }

        crosshairSprite.setPosition(localPosition.x-38,localPosition.y);
        sprite.move(speed * delta, 0.f);
        sprite.getGlobalBounds().intersects(crosshairSprite.getGlobalBounds());
        window.draw(sprite);
        window.draw(crosshairSprite);
        window.display();
    }

    return 0;
}

// this is a workaround to make the game run on Windows without a console window
#ifdef _MSC_VER
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    return main(__argc, __argv);
}
#endif