#include "header.h"

const int sizeofscreenx = 1800;
const int sizeofscreeny = 700;
float k_size = 1;
Vector2f corKam = Vector2f(sizeofscreenx, sizeofscreeny);

int main()
{
    srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    sf::Clock clock;
    sf::ContextSettings settings;
    Player player;
    vector<Enemy> enemy;

    for (int i = 0; i < 5; ++i) enemy.push_back(Enemy(&player));

    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(sizeofscreenx, sizeofscreeny), "Game Ball", sf::Style::Default, settings);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        player.control();
        for (int i = 0; i < 5; ++i) {
            enemy[i].control();
        }

        if (keyboard.isKeyPressed(Keyboard::F)) {
            player.body_resize(0.001);
            for (int i = 0; i < 5; ++i) {
                enemy[i].body_resize(0.001);
            }
        }
        if (keyboard.isKeyPressed(Keyboard::C)) {
            player.body_resize(-0.001);
            for (int i = 0; i < 5; ++i) {
                enemy[i].body_resize(-0.001);
            }
        }
        
        //Без эффектов
        //window.clear();
        //

        //Моушн блюр
        RectangleShape forBlurClear;
        forBlurClear.setSize(Vector2f(window.getSize()));
        forBlurClear.setFillColor(Color(255, 255, 255, 20));
        window.draw(forBlurClear);
        //

        window.draw(player.getBody());
        for (int i = 0; i < 5; ++i) {
            window.draw(enemy[i].getBody());
        }
        //window.draw(player.getDebug());
        window.display();
    }

    return 0;
}

int sign(float a) {
    if (a >= 0) return 1;
    else return -1;
}

Vector2f toOneVec(Vector2f vec) {
    if (pow(vec.x * vec.x + vec.y * vec.y, 0.5) == 0) return Vector2f(0, 0);
    Vector2f newVec(vec.x, vec.y);
    newVec.x /= pow(vec.x * vec.x + vec.y * vec.y, 0.5);
    newVec.y /= pow(vec.x * vec.x + vec.y * vec.y, 0.5);
    return newVec;
}

float mod(Vector2f vec) {
    return pow(vec.x * vec.x + vec.y * vec.y, 0.5);
}

float hiperbola(float x) {
    if (x <= 0.001) return 1000;
    return x;
}

Vector2f rotateVector(Vector2f vec, float ang) {
    float angle = abs(ang) * M_PI / 180.0f;
    float cos_a = std::cos(angle);
    float sin_a = std::sin(angle);

    if (ang < 0) {
        sin_a = -sin_a;  // меняем знак синуса для поворота в другую сторону
    }

    Vector2f ans = Vector2f(
        vec.x * cos_a - vec.y * sin_a,
        vec.x * sin_a + vec.y * cos_a
    );
    return ans;
}