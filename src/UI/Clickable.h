#pragma once

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Clickable : public virtual Rectangle {
public:
    Clickable(sf::Vector2f size, sf::Color color, sf::Color hoverColor, sf::Color clickColor);
    void checkCursorOn(sf::RenderWindow & window);
    virtual void onClick();
    virtual ~Clickable();
private:
    bool isClicked = false;
    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color clickColor;
};
