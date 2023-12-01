#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <SFML/Graphics.hpp>

using namespace sf;


class Utilitaire {
public:
    static float distancei(const Vector2i& v1, const Vector2i& v2);
    static float distanceCarrei(const Vector2i& v1, const Vector2i& v2);
    static float distancef(const Vector2f& v1, const Vector2f& v2);
    static float distanceCarref(const Vector2f& v1, const Vector2f& v2);
    static void adjustView(RenderWindow& window, View& view, int viewWidthTiles, int viewHeightTiles);
};


#endif