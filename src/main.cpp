#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>

int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "QuackAttack" };
    window.setFramerateLimit(144);

    sf::RectangleShape shape(sf::Vector2f(120, 50));

    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));

    sf::Texture texture;
    if (!texture.loadFromFile("Textures/Duck.png"))
    {
        std::cout << "Error";
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
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

        shape.setPosition(localPosition.x-10,localPosition.y-10);
        window.draw(sprite);
        window.draw(shape);
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