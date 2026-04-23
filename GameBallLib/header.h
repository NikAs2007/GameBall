#pragma once

#define M_PI 3.141592
#define ASIO_STANDALONE

#include <asio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;
using namespace sf;

extern Keyboard keyboard;
extern Mouse mouse;
extern const int sizeofscreenx;
extern const int sizeofscreeny;
//extern float k_size;
//extern Vector2f corKam;

int sign(float a);
Vector2f toOneVec(Vector2f vec);
float mod(Vector2f vec);
float hiperbola(float x);
Vector2f rotateVector(Vector2f vec, float angle);

struct PlayerKeyboard {
	bool up = false, down = false, right = false, left = false;

	PlayerKeyboard() {};

	PlayerKeyboard(PlayerKeyboard& pk) {
		*this = pk;
	}
};

struct Body {
	CircleShape body;
	float rad = 10;
	Vector2f cor;
	float rotation;

	//void setRad(float rad);
	//CircleShape& getBody() {
	//	return body;
	//}
	virtual void polimorphicCl() {};
};

class Player : public Body{
	Vector2f acs;
	Vector2f vel;
	float mass = 500;
	float power = 2;
	float kfr = 0.3;
	float kai = 1.5;
	int id = 0;

	Text dtext;
	static Font font;

	friend class Enemy;

public:
	PlayerKeyboard pk;

	Player(int id);
	Text getDebug();
	Vector2f calc_acs(Vector2f vec);
	void control();
	CircleShape getBody();
	int getId();
};

class Enemy : public Body {
	Vector2f acs;
	Vector2f vel;
	float mass = 500;
	float power = 3;
	float kfr = 0.05;
	float kai = 2;

	Player* target;
public:
	Enemy(Player* target);
	Vector2f calc_acs(Vector2f vec);
	void control();
	CircleShape getBody();
};

class Button : public Body {

public:
	bool isHover(RenderWindow& window) {
		if (mod(Vector2f(mouse.getPosition(window)) - body.getPosition()) <= rad) {
			rad = 55;
			body.setRadius(rad);
			body.setFillColor(Color(200,245,255));
			return true;
		}
		rad = 50;
		body.setRadius(rad);
		body.setFillColor(Color(255,255,255));
		return false;
	}

	Button() {
		rad = 50;
		cor = Vector2f(0, 0);
		body.setFillColor(Color(255, 255, 255, 255));
		body.setOrigin(rad, rad);
		body.setPointCount(64);
		body.setRadius(rad);
	}
};

class Menu {

public:
	vector<Button> buttons;
	enum Stage { MENU, PAUSE, PLAY };
	Stage stage = MENU;

	Menu();
	
};

class Camera {
	vector<Body*>* bodies;
	Menu* menu;
	RenderWindow* window;
	float k_size = 1;
	Vector2f corKam = Vector2f(0, 0);

	Shader blinks;
	Shader screen_sh;
	Clock clock;

	RenderTexture rendTexture;
	Sprite picture;

public:
	Camera(RenderWindow* window, vector<Body*>* bodies, Menu* menu);
	void control();
	void draw_all();
};