#include "header.h"

const int sizeofscreenx = 1800;
const int sizeofscreeny = 700;

int main()
{
    sf::Clock clock;
    sf::ContextSettings settings;
    Player player;

    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(sizeofscreenx, sizeofscreeny), "SFML test", sf::Style::Default, settings);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        player.control();

        if (keyboard.isKeyPressed(Keyboard::F)) player.body_resize(0.001);
        if (keyboard.isKeyPressed(Keyboard::C)) player.body_resize(-0.001);
        
        window.clear();
        window.draw(player.getBody());
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