#include "region.h"

Region::Region(int x, int y, int width, int height) : rect(x, y, width, height) {}

bool Region::contains(int x, int y) const {
    return rect.contains(x, y);
}

bool Region::intersects(const Region& other) const {
    return rect.intersects(other.rect);
}

void Region::setPosition(int x, int y) {
    rect.left = x;
    rect.top = y;
}

void Region::setSize(int width, int height) {
    rect.width = width;
    rect.height = height;
}

sf::Vector2f Region::getPosition() const {
    return Vector2f(rect.left, rect.top);
}

sf::Vector2f Region::getSize() const {
    return Vector2f(rect.width, rect.height);
}

