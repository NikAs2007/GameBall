#include "header.h"

Camera::Camera(RenderWindow* window, vector<Body*>* bodies) {
	this->window = window;
	this->bodies = bodies;

	rendTexture.create(sizeofscreenx, sizeofscreeny);
	picture.setTexture(rendTexture.getTexture());

	blinks.loadFromFile("shaders/shader.frag", Shader::Fragment);
	screen_sh.loadFromFile("shaders/screen_shader.frag", Shader::Fragment);
}

void Camera::control() {
    if (keyboard.isKeyPressed(Keyboard::F)) {
		k_size += 0.01;
	}
	if (keyboard.isKeyPressed(Keyboard::C)) {
		k_size -= 0.01;
		if (k_size <= 0) k_size = 0.01;
	}

	if (keyboard.isKeyPressed(Keyboard::Up)) {
		corKam.y -= 3 * k_size;
	}
	if (keyboard.isKeyPressed(Keyboard::Down)) {
		corKam.y += 3 * k_size;
	}
	if (keyboard.isKeyPressed(Keyboard::Left)) {
		corKam.x -= 3 * k_size;
	}
	if (keyboard.isKeyPressed(Keyboard::Right)) {
		corKam.x += 3 * k_size;
	}


	//if (event.type == sf::Event::KeyPressed) {
	//	if (event.key.code == sf::Keyboard::R) {
	//		moutionblur = !moutionblur;
	//	}
	//}
	

	// Для R используем отдельный флаг
	static bool r_was_pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		if (!r_was_pressed) {
			r_was_pressed = true;
			moutionblur = !moutionblur;
			std::cout << "Motion blur: " << (moutionblur ? "ON" : "OFF") << std::endl;
		}
	}
	else {
		r_was_pressed = false;
	}

}

void Camera::draw_all() {
	if (!moutionblur) {
		float time_ = clock.getElapsedTime().asSeconds();

		window->clear(Color(0, 0, 0));
		rendTexture.clear();
	}
	else {
		RectangleShape forBlurClear;
		forBlurClear.setSize(Vector2f(window->getSize()));
		forBlurClear.setFillColor(Color(255, 255, 255, 20));
		window->draw(forBlurClear);
		//window->clear(Color(255, 0, 0));
	}
	for (int i = 0; i < bodies->size(); ++i) {
		(*bodies)[i]->body.setPosition(((*bodies)[i]->cor.x - corKam.x) / k_size + (float)sizeofscreenx/2, ((*bodies)[i]->cor.y - corKam.y) / k_size + (float)sizeofscreeny/2);
		(*bodies)[i]->body.setRadius((*bodies)[i]->rad / k_size);
		(*bodies)[i]->body.setOrigin((*bodies)[i]->rad / k_size, (*bodies)[i]->rad / k_size);

		blinks.setUniform("cenx", (*bodies)[i]->body.getPosition().x);
		blinks.setUniform("ceny", sizeofscreeny - (*bodies)[i]->body.getPosition().y);
		blinks.setUniform("zoom", k_size);

		Player* isPlayer = dynamic_cast<Player*>((*bodies)[i]);
		if (isPlayer) {
			rendTexture.draw((*bodies)[i]->body, &blinks);
			//window->draw((*bodies)[i]->body, &blinks);
		}
		else {
			rendTexture.draw((*bodies)[i]->body);
			//window->draw((*bodies)[i]->body);
		}
	}
	rendTexture.display();
	screen_sh.setUniform("u_texture",rendTexture.getTexture());
	screen_sh.setUniform("strength", 0.002f);
	screen_sh.setUniform("zoom", k_size);
	window->draw(picture, &screen_sh);
	window->display();
}