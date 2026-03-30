#pragma once

#define M_PI 3.141592

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;
using namespace sf;

extern Keyboard keyboard;
extern const int sizeofscreenx;
extern const int sizeofscreeny;
extern float k_size;
extern Vector2f corKam;

int sign(float a);
Vector2f toOneVec(Vector2f vec);
float mod(Vector2f vec);
float hiperbola(float x);
Vector2f rotateVector(Vector2f vec, float angle);

class Player {
	CircleShape body;
	Vector2f acs;
	Vector2f vel;
	float mass = 500;
	float power = 2;
	float kfr = 0.3;
	float kai = 1.5;
	float rad = 10;

	Vector2f cor;
	//Vector2f corKam;

	Text dtext;
	static Font font;

	friend class Enemy;
public:
	Player();
	Text getDebug();
	void body_resize(float k);
	Vector2f calc_acs(Vector2f vec);
	void control();
	CircleShape getBody();
};

class Enemy {
	CircleShape body;
	Vector2f acs;
	Vector2f vel;
	float mass = 500;
	float power = 3;
	float kfr = 0.05;
	float kai = 2;
	float rad = 10;

	Vector2f cor;
	//Vector2f corKam;

	Player* target;
public:
	Enemy(Player* target);
	void body_resize(float k);
	Vector2f calc_acs(Vector2f vec);
	void control();
	CircleShape getBody();
};

