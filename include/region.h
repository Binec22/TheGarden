#ifndef REGION_H
#define REGION_H

#include <SFML/Graphics.hpp>

using namespace sf;

// Classe non utilisée
// Je l'avais prévue pour définir des régions sur les champs
// pour ne pouvoir detruire des choses que dans les champs

class Region {
private:
    sf::Rect<int> rect;

public:
    Region(int x, int y, int width, int height);
    bool contains(int x, int y) const;
    bool intersects(const Region& other) const;
    void setPosition(int x, int y);
    void setSize(int width, int height);
    Vector2f getPosition() const;
    Vector2f getSize() const;
    ~Region();
};


#endif
