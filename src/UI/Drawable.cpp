#include "Drawable.h"

Rectangle::Rectangle(sf::Vector2f size, sf::Color color) : shape(size) {
    shape.setFillColor(color);
}
void Rectangle::draw(sf::RenderTarget & target, sf::Vector2f position) const {
    sf::RectangleShape tempShape = shape;
    tempShape.setPosition(position);
    target.draw(tempShape);
}

void Rectangle::setPosition(sf::Vector2f position) {
    this->position = position;
    this->shape.setPosition(position);
}

DrawableDecorator::DrawableDecorator (Drawable & drawable) : wrappee(drawable) {
    this->position = drawable.position;
}

void DrawableDecorator::draw(sf::RenderTarget & target, sf::Vector2f position) const {
    wrappee.draw(target, position);
}

BorderDecorator::BorderDecorator (Rectangle & drawable, float thickness, sf::Color color) 
    : DrawableDecorator(drawable) {
    border.setSize({drawable.shape.getSize().x, drawable.shape.getSize().y});
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(color);
    border.setOutlineThickness(thickness);
}

void BorderDecorator::draw(sf::RenderTarget & target, sf::Vector2f position) const {
    
    sf::RectangleShape tempBorder = border;
    tempBorder.setPosition(
        sf::Vector2f (position.x, position.y)
    );
    target.draw(tempBorder);
    wrappee.draw(target, position);
}