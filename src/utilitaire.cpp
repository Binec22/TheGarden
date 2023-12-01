#include "utilitaire.h"
#include <cmath>

using namespace std;

float Utilitaire::distancei(const Vector2i &v1, const Vector2i &v2)
{
    return sqrt(pow(v1.x - v2.x, 2) + pow(v2.y - v1.y, 2));
}
float Utilitaire::distanceCarrei(const Vector2i &v1, const Vector2i &v2)
{
    return pow(v1.x - v2.x, 2) + pow(v2.y - v1.y, 2);
}
float Utilitaire::distancef(const Vector2f &v1, const Vector2f &v2)
{
    return sqrt(pow(v1.x - v2.x, 2) + pow(v2.y - v1.y, 2));
}
float Utilitaire::distanceCarref(const Vector2f &v1, const Vector2f &v2)
{
    return pow(v1.x - v2.x, 2) + pow(v2.y - v1.y, 2);
}

void Utilitaire::adjustView(RenderWindow &window, View &view, int viewWidthTiles, int viewHeightTiles)
{    
    float windowRatio = float(window.getSize().x) / float(window.getSize().y);
    float viewRatio = float(viewWidthTiles) / float(viewHeightTiles);
    float sizeX, sizeY;

    if (windowRatio > viewRatio) {
        sizeX = viewHeightTiles * windowRatio * 16;
        sizeY = viewHeightTiles * 16;
    } else {
        sizeX = viewWidthTiles * 16;
        sizeY = viewWidthTiles / windowRatio * 16;
    }

    view.setSize(sizeX, sizeY);
    view.setCenter(sizeX / 2, sizeY / 2);
}