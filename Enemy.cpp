#include "header.h"

//Keyboard keyboard;

Enemy::Enemy(Player* target) {
	body.setFillColor(Color::Blue);
	body.setPointCount(3);
	body.setRadius(rad);
	body.setRotation(0);
	body.setOrigin(rad, rad);
	vel = Vector2f(0, 0);
	acs = Vector2f(0, 0);
	cor = Vector2f(100, 100);
	body.setPosition(cor.x, cor.y);
	corKam = Vector2f(sizeofscreenx, sizeofscreeny);

	this->target = target;
}

//void Player::body_resize(float k) {
//	k_size += k;
//	//body.setPosition(body.getPosition().x / hiperbola(scroll), body.getPosition().y / hiperbola(scroll));
//	//body.setRadius(b)
//}

Vector2f Enemy::calc_acs(Vector2f vec) {
	return (power * vec - kfr * toOneVec(vel) - toOneVec(vel) * kai * mod(vel) * mod(vel)) / mass;
}

void Enemy::control() {
	Vector2f vec(0, 0);

	//Вычислить направление к игроку (vec)

	vec = target->cor - this->cor;

	vec = toOneVec(vec);
	if ((vec.x * vel.x + vec.y * vel.y) / mod(vec) / mod(vel) < 0.5) {
		//доделать поворот вектора на 30 градусов

		Vector2f dir = Vector2f(target->cor.x - cor.x, target->cor.y - cor.y);

		// Векторное произведение (2D псевдоскалярное)
		float cross = vel.x * dir.y - vel.y * dir.x;

		float angle = 60.0f * M_PI / 180.0f;
		float cos_a = std::cos(angle);
		float sin_a = std::sin(angle);

		// Если cross > 0, цель слева, поворачиваем налево (против часовой)
		// Если cross < 0, цель справа, поворачиваем направо (по часовой)
		if (cross < 0) {
			sin_a = -sin_a;  // меняем знак синуса для поворота в другую сторону
		}

		vec = Vector2f(
			vel.x * cos_a - vel.y * sin_a,
			vel.x * sin_a + vel.y * cos_a
		);
	}

	acs = calc_acs(vec);
	vel += acs;
	body.setRotation(atan2(-toOneVec(vec).x, toOneVec(vec).y)*180/3.1415f - 60);
	cor.x = cor.x + vel.x;
	cor.y = cor.y + vel.y;

	body.setPosition((cor.x - corKam.x / 2) / k_size + corKam.x / 2, (cor.y - corKam.y / 2) / k_size + corKam.y / 2);
	body.setRadius(rad / k_size);
	//if (toOneVec(vel).y != 0) body.setRotation(atanf(toOneVec(vel).x / toOneVec(vel).y)*180/M_PI);
}

CircleShape Enemy::getBody() {
	return body;
}