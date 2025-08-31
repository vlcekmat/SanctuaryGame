#pragma once

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Clickable : public virtual Rectangle {
public:
    Clickable(sf::Vector2f size, sf::Color color) : Rectangle(size, color) {}
    void checkCursorOn(sf::RenderWindow & window);
    virtual ~Clickable();
};
