#include "header.h"

//Keyboard keyboard;

Player::Player(){
	rad = 20;
	body.setFillColor(Color::Green);
	body.setPointCount(16);
	body.setRadius(rad);
	body.setRotation(0);
	body.setOrigin(rad/2, rad/2);
	vel = Vector2f(0, 0);
	acs = Vector2f(0, 0);
	cor = Vector2f(sizeofscreenx/2, sizeofscreeny / 2);
	body.setPosition(cor.x, cor.y);
	//corKam = Vector2f(sizeofscreenx, sizeofscreeny);

	//if (!font.loadFromFile("ArialBlack.ttf")) cerr << "Font error!\n";
	//dtext.setFont(font);
	//dtext.setPosition(10, 10);
	//dtext.setCharacterSize(10);
	//dtext.setFillColor(Color(255, 255, 255));

}

Vector2f Player::calc_acs(Vector2f vec) {
	return (power*vec - kfr*toOneVec(vel) - toOneVec(vel) * kai * mod(vel) * mod(vel)) / mass;
}

void Player::control() {
	Vector2f vec(0, 0);

	if (keyboard.isKeyPressed(Keyboard::W)) {
		vec.y += 1;
	}
	if (keyboard.isKeyPressed(Keyboard::S)) {
		vec.y -= 1;
	}
	if (keyboard.isKeyPressed(Keyboard::A)) {
		vec.x -= 1;
	}
	if (keyboard.isKeyPressed(Keyboard::D)) {
		vec.x += 1;
	}
	vec = toOneVec(vec);
	acs = calc_acs(vec);
	vel += acs;
	cor.x = cor.x + vel.x;
	cor.y = cor.y - vel.y;

	//body.setPosition((cor.x - corKam.x / 2) / k_size + corKam.x / 2, (cor.y - corKam.y / 2) / k_size + corKam.y / 2);
	//body.setRadius(rad / k_size);
	
	//if (toOneVec(vel).y != 0) body.setRotation(atanf(toOneVec(vel).x / toOneVec(vel).y)*180/M_PI);
}

CircleShape Player::getBody() {
	return body;
}

Text Player::getDebug() {
	dtext.setString("Vel x: " + to_string(vel.x) + "\nVel y: " + to_string(vel.y));
	return dtext;
}