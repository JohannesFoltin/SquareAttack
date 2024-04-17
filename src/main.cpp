#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>
#include "Duck.h"

int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "QuackAttack" };
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(144);

    sf::View view;
    view.setCenter(sf::Vector2f(960.f, 540.f));
    view.setSize(sf::Vector2f(1920.f, 1080.f));
    window.setView(view);

    // Our speed in pixels per second
    float speed = 100.f;
    // Our clock to time frames
    sf::Clock clock;

    sf::Texture crosshair;
    crosshair.loadFromFile("textures/Crosshair.png");
    
    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshair);
    crosshairSprite.setScale(0.125, 0.125);

    Duck duck1(100, sf::Vector2f(0.0f,0.0f),sf::Vector2f(1.0f,1.0f));


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

       // std::cout << localPosition.x << "  "<< localPosition.y << "\n";

        if (localPosition.x < 0 || localPosition.y < 0)
        {
        }

        crosshairSprite.setPosition(localPosition.x-38,localPosition.y);
        duck1.update(delta);
        window.draw(duck1.sprite);
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