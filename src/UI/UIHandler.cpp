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

    Clickable clickableRect({100, 100}, sf::Color::White, sf::Color::Green, sf::Color::Red);
    clickableRect.setPosition({200, 200});

    BorderDecorator rectWithDec = BorderDecorator(clickableRect, 5.0f, sf::Color::Yellow);
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

        
        clickableRect.checkCursorOn(window);
        rectWithDec.draw(window, {200, 200});

        // --------------------------------------------------
        window.display();
    }
}

