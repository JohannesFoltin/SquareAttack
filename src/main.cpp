#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>
#include "Duck.h"


int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow{{ 1920u, 1080u }, "Square Shooter",sf::Style::Close | sf::Style::Titlebar };

    window.setSize(sf::Vector2u(1920, 1080));

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
    crosshairSprite.setScale(0.1, 0.1);

    Square square = Square(200, sf::Vector2f(960.0f,540.0f), sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1920.f, 1080.0f));

    int score = 0;

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();


        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (square.sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == 1) {
                        score = score + 1;
                        square.reset();
                    }
                }
            }
        }

        window.clear(sf::Color(250,250,250));

        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        crosshairSprite.setPosition(localPosition.x-31,localPosition.y-2);

        square.update(delta);

        window.draw(square.sprite);
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