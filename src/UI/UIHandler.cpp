#include "UIHandler.h"

#define GAME_NAME "The Harvest Guild"

void UIHandler::handleUI() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), GAME_NAME);
    window.setVerticalSyncEnabled(true);

    sf::Font font("./assets/Fonts/dogica/TTF/dogica.ttf");

    sf::Text text(font);
    text.setString(GAME_NAME);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({200, 280});

    Rectangle rect({50, 50}, sf::Color(50, 50, 50));
    Clickable clickableRect({100, 100}, sf::Color::White);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        // draw everything here...

        window.draw(text);

        rect.draw(window, {10, 10});

        clickableRect.setPosition({200, 200});
        clickableRect.checkCursorOn(window);
        clickableRect.draw(window, {200, 200});

        // --------------------------------------------------
        window.display();
    }
}

