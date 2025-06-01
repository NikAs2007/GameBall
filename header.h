#pragma once

#define M_PI 3.141592

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

extern Keyboard keyboard;
extern const int sizeofscreenx;
extern const int sizeofscreeny;

int sign(float a);
Vector2f toOneVec(Vector2f vec);
float mod(Vector2f vec);
float hiperbola(float x);

class Player {
	CircleShape body;
	Vector2f acs;
	Vector2f vel;
	float mass = 500;
	float power = 2;
	float kfr = 0.3;
	float kai = 1.5;
	float rad = 10;

	float k_size = 1;
	Vector2f cor;
	Vector2f corKam;
public:
	Player();
	void body_resize(float k);
	Vector2f calc_acs(Vector2f vec);
	void control();
	CircleShape getBody();
};