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