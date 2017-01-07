#include "Madness_drivers.h"

const double pi = 3.1415926535897;
const double eps = 0.000000001;
int numberOfTries, maximumNumberOfTries = 100;
bool haveAttempts() {
    if(numberOfTries >= maximumNumberOfTries)
        return 0;

    return 1;
}
Vector2f translate(Vector2f p, double angle, double distance) {
    Vector2f pos;
    pos.x = p.x + distance * cos(angle);
    pos.y = p.y + distance * sin(angle);
    return pos;
}
double min(double x, double y) {
    return x < y ? x : y;
}
//angle in degree
double Get(Vector2f pos, double angle) {
    if(!haveAttempts())
        return 0;// No more attempts

    if(!isIn(pos))
        return -1;// position is outside the map

    numberOfTries++;
    double m, ret = 2000, i = 2000;
    angle  = angle * pi / 180.0;
    Vector2f newPos;

    while(i) {
        double l = eps, r = i;

        while(l + eps < r) {
            m = (l + r) / 2;
            newPos = translate(pos, angle, m);

            if(isIn(newPos))
                l = m;
            else
                r = m;
        }

        ret = min(ret, m);
        i -= 100;
    }

    return ret;
}
Vector2f Start() {
    return GetPlayerStartPositions();
}
bool onSegment(Vector2f a, Vector2f c, Vector2f b) {
    if(dist(a, c) + dist(c, b) == dist(a, b))
        return 1;

    return 0;
}
double crossProduct(Vector2f a, Vector2f c, Vector2f b) {
    return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}
bool intrsects(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    if(crossProduct(a, b, c)*crossProduct(a, b, d) < 0 && crossProduct(c, d, a)*crossProduct(c, d, b) < 0)
        return 1;

    if(onSegment(a, c, b) || onSegment(a, d, b) || onSegment(c, a, d) || onSegment(c, b, d))
        return 1;

    return 0;
}
// Move returns 1 if player not finished yet and makes the movement, else returns 0
bool Move(Vector2f myPos, Vector2f newPos) {
    if(intersects(finishLocation[0], finishLocation[1], myPos, newPos))
        return 0;

    doMove(myPos, newPos);
    return 1;
}
