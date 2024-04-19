#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>
#include "square.h"

static std::string generateGameStateString(int score, int bullets) {
    return "Score: " + std::to_string(score) + " " + "Bullets left: " + std::to_string(bullets);
}

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

    sf::Clock clock;

    sf::Texture crosshair;
    crosshair.loadFromFile("textures/Crosshair.png");
    
    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshair);
    crosshairSprite.setScale(0.1, 0.1);

    const int startSpeed = 150;
    Square square = Square(startSpeed, sf::Vector2f(1920.f, 1080.0f));

    sf::Font font;

    //The one and only font :)
    if (!font.loadFromFile("font/comicsans.ttf"))
    {
        std::cout << "Error";
    }
    
    int score = 0;
    int bullets = 3;

    sf::Text gameStateText;
    gameStateText.setFont(font); 
    gameStateText.setString(generateGameStateString(score,bullets));
    gameStateText.setCharacterSize(24);
    gameStateText.setColor(sf::Color(0.0f, 0.0f, 0.0f));
    gameStateText.setPosition(6, 6);

    sf::Text stateText;
    stateText.setFont(font);
    stateText.setString("Game Over. Press left click to start again.");
    stateText.setCharacterSize(50);
    stateText.setFillColor(sf::Color::Red);
    stateText.setPosition(540.0f, 380.0f);

    bool ingame = true;

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
                    if (ingame)
                    {
                        if (square.sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == 1) {
                            score = score + 1;
                            bullets = 3;
                            gameStateText.setString(generateGameStateString(score,bullets));
                            square.reset();
                            square.increaseSpeed(5);
                        }
                        else {
                            bullets = bullets - 1;
                            gameStateText.setString(generateGameStateString(score, bullets));
                            if (bullets == 0)
                            {
                                ingame = false;
                                square.resetSpeed(startSpeed);
                                square.gameOver();
                            }
                        }
                    }
                    else {
                        ingame = true;
                        bullets = 3;
                        score = 0;
                        gameStateText.setString(generateGameStateString(score, bullets));
                    }
            }
        }

        window.clear(sf::Color(250,250,250));

        if (ingame)
        {
            square.update(delta);
        }
        else {
            window.draw(stateText);
        }

        window.draw(square.sprite);
        
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        crosshairSprite.setPosition(localPosition.x-31,localPosition.y-2);
        window.draw(crosshairSprite);

        window.draw(gameStateText);

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