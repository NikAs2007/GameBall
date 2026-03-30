#include "header.h"

Camera::Camera(RenderWindow* window, vector<Body*>* bodies) {
	this->window = window;
	this->bodies = bodies;
}

void Camera::control() {
    if (keyboard.isKeyPressed(Keyboard::F)) {
		k_size += 0.01;
	}
	if (keyboard.isKeyPressed(Keyboard::C)) {
		k_size -= 0.01;
	}

	if (keyboard.isKeyPressed(Keyboard::Up)) {
		corKam.y += 10;
	}
	if (keyboard.isKeyPressed(Keyboard::Down)) {
		corKam.y -= 10;
	}
	if (keyboard.isKeyPressed(Keyboard::Left)) {
		corKam.x += 10;
	}
	if (keyboard.isKeyPressed(Keyboard::Right)) {
		corKam.x -= 10;
	}
}

void Camera::draw_all() {
	window->clear(Color(0, 0, 0));
	for (int i = 0; i < bodies->size(); ++i) {
		(*bodies)[i]->body.setPosition(((*bodies)[i]->cor.x - corKam.x / 2) / k_size + corKam.x / 2, ((*bodies)[i]->cor.y - corKam.y / 2) / k_size + corKam.y / 2);
		(*bodies)[i]->body.setRadius((*bodies)[i]->rad / k_size);
		window->draw((*bodies)[i]->body);
	}
	window->display();
}