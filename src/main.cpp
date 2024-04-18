#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>
#include "square.h"


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

    sf::Font font;
    if (!font.loadFromFile("font/comicsans.ttf"))
    {
        std::cout << "Error";
    }
    
    int score = 0;
    int bulllets = 4;

    sf::Text scoreText;
    scoreText.setFont(font); 
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color(0.0f, 0.0f, 0.0f));
    scoreText.setPosition(6, 1050);

    sf::Text bulletText;
    bulletText.setFont(font);
    bulletText.setString("Bullets left: " + std::to_string(bulllets));
    bulletText.setCharacterSize(24);
    bulletText.setColor(sf::Color(0.0f, 0.0f, 0.0f));
    bulletText.setPosition(150, 1050);


    sf::Text stateText;
    stateText.setFont(font);
    stateText.setString("Game Over. Press left click to start again.");
    stateText.setCharacterSize(50);
    stateText.setFillColor(sf::Color::Red);
    stateText.setPosition(540.0f, 480.0f);

    bool ingame = false;

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
                    if (ingame)
                    {
                        if (square.sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == 1) {
                            score = score + 1;
                            scoreText.setString("Score: " + std::to_string(score));
                            square.reset();
                        }
                        else {
                            if (bulllets == 1)
                            {
                                ingame = false;
                                square.gameOver();
                            }
                            bulllets = bulllets - 1;
                            bulletText.setString("Bullets left: " + std::to_string(bulllets));
                        }
                    }
                    else {
                        ingame = true;
                        bulllets = 4;
                        score = 0;
                        bulletText.setString("Bullets left: " + std::to_string(bulllets));
                        scoreText.setString("Score: " + std::to_string(score));
                    }
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

        window.draw(scoreText);
        window.draw(bulletText);

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