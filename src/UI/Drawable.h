#include <SFML/Graphics.hpp>

#pragma once

class Drawable {
public:
    virtual void draw(sf::RenderTarget & target, sf::Vector2f position) const = 0;
    virtual ~Drawable() = default;
    sf::Vector2f position;
};

// -------------------------------------------------------------------------------------------------------------------------

class Rectangle : public virtual Drawable {
public:
    Rectangle(sf::Vector2f size, sf::Color color);
    sf::RectangleShape shape;
    void draw(sf::RenderTarget & target, sf::Vector2f position) const override;
    virtual void setPosition(sf::Vector2f position);
    virtual ~Rectangle() = default;
};