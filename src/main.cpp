#include <SFML/Graphics.hpp>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <iostream>
#include "square.h"

// Handles the int to String and returns the result string for the gameStateText
static std::string generateGameStateString(int score, int bullets) {
    return "Score: " + std::to_string(score) + " " + "Bullets left: " + std::to_string(bullets);
}

int main(int argc, char* argv[])
{
    // Window definition
    auto window = sf::RenderWindow{{ 1920u, 1080u }, "Square Shooter",sf::Style::Close | sf::Style::Titlebar };

    window.setSize(sf::Vector2u(1920, 1080));

    //Makes the mousecursor unvisible 
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(144);

    // Gives the Window a coordinate system to work with
    sf::View view;
    view.setCenter(sf::Vector2f(960.f, 540.f));
    view.setSize(sf::Vector2f(1920.f, 1080.f));
    window.setView(view);

    // Init of the Clock to track the delta for movement calculations
    sf::Clock clock;

    // Loading the Crosshair texture
    sf::Texture crosshair;
    crosshair.loadFromFile("textures/Crosshair.png");
    
    // Init of the Sprite, so the texture can be rendered
    sf::Sprite crosshairSprite;
    crosshairSprite.setTexture(crosshair);
    crosshairSprite.setScale(0.1, 0.1);

    const int startSpeed = 150;

    // Init of the Square class
    Square square = Square(startSpeed, sf::Vector2f(1920.f, 1080.0f));

    sf::Font font;

    //The one and only font :)
    if (!font.loadFromFile("font/comicsans.ttf"))
    {
        std::cout << "Error";
    }

    // Everything related to the Gamestate
    int score = 0;
    int bullets = 3;

    // Text that displays the current score and the bullets left
    sf::Text gameStateText;
    gameStateText.setFont(font); 
    gameStateText.setString(generateGameStateString(score,bullets));
    gameStateText.setCharacterSize(24);
    gameStateText.setColor(sf::Color(0.0f, 0.0f, 0.0f));
    gameStateText.setPosition(6, 6);

    // Text that is shown when the game is over
    sf::Text stateText;
    stateText.setFont(font);
    stateText.setString("Game Over. Press left click to start again.");
    stateText.setCharacterSize(50);
    stateText.setFillColor(sf::Color::Red);
    stateText.setPosition(540.0f, 380.0f);

    bool ingame = true;

    while (window.isOpen())
    {
        // Delta is used to calculate the distance that the square traveld within one frame
        float delta = clock.restart().asSeconds();

        // Event handling
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Checks if the left mouse button is pressed
            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
                    if (ingame)
                    {
                        // Checks if the mousepointer is inside of the Square
                        if (square.sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == 1) {
                            score = score + 1;
                            bullets = 3;
                            gameStateText.setString(generateGameStateString(score,bullets));
                            // Moves the square to a new Position
                            square.reset();
                            square.increaseSpeed(5);
                        }
                        // The player didnt hit the square :/
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
                    // If the game is not running. Restart it
                    else {
                        ingame = true;
                        bullets = 3;
                        score = 0;
                        gameStateText.setString(generateGameStateString(score, bullets));
                    }
            }
        }
        // Makes the Window white
        window.clear(sf::Color(250,250,250));

        if (ingame)
        {
            // Do the calculations for the Frame
            square.update(delta);
        }
        else {
            // If the game is not running display this text
            window.draw(stateText);
        }

        // Render the square
        window.draw(square.sprite);

        // Move the Crosshair texture to the invisble Mouse
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        crosshairSprite.setPosition(localPosition.x-31,localPosition.y-2);
        //Draw the Crosshair
        window.draw(crosshairSprite);
        // Draw the score etc.
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