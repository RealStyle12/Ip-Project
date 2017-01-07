#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Car.h"
#include "Menu.h"
#include "box.h"

using namespace std;
using namespace sf;

double Get(Vector2f pos, double angle);
Vector2f Start();
bool Move(Vector2f myPos, Vector2f newPos);
Vector2f translate(Vector2f p, double angle, double distance)

