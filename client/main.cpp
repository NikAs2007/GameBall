//client

#include "../GameBallLib/header.h"
#include <array>
#include <fstream>

const int sizeofscreenx = 1800;
const int sizeofscreeny = 700;

#pragma pack(push, 1)
struct StatePacket {
    float px, py;
    array<float, 50 * 2> cords;
    array<float, 51> rots;
    //Menu menu;
    Menu::Stage stage;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct InputPacket {
    int id;
    PlayerKeyboard pk;
};
#pragma pack(pop)

int main()
{
    //-----
    std::ofstream debug("../debug/debug.txt");
    debug << sizeof(InputPacket);
    debug.close();


    //------


    //----------------------------------------------
    asio::io_context io;
    asio::ip::udp::socket socket(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)); // любой свободный порт
    socket.non_blocking(true);
    asio::ip::udp::endpoint server(asio::ip::make_address("127.0.0.1"), 56782);
    //----------------------------------------------

    srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
    sf::Clock clock;
    sf::ContextSettings settings;
    Player player(1);
    vector<Enemy> enemy;

    for (int i = 0; i < 50; ++i) enemy.push_back(Enemy(&player));

    vector<Body*> bodies;
    bodies.push_back(&player);
    for (int i = 0; i < 50; ++i) bodies.push_back(&enemy[i]);


    settings.antialiasingLevel = 5;
    sf::RenderWindow window(sf::VideoMode(sizeofscreenx, sizeofscreeny), "Game Ball", sf::Style::Default, settings);
    Menu menu;
    Camera cam(&window, &bodies, &menu);
    bool fl = false;
    bool fl_pause = false;

    StatePacket pck;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        socket.non_blocking(true);
        asio::ip::udp::endpoint sender;
        asio::error_code ec;

        // Отправляем приветствие для регистрации
        InputPacket inp;
        inp.id = 1;
        if (keyboard.isKeyPressed(Keyboard::W)) {
            inp.pk.up = true;
        }
        if (keyboard.isKeyPressed(Keyboard::S)) {
            inp.pk.down = true;
        }
        if (keyboard.isKeyPressed(Keyboard::A)) {
            inp.pk.left = true;
        }
        if (keyboard.isKeyPressed(Keyboard::D)) {
            inp.pk.right = true;
        }
        socket.send_to(asio::buffer(&inp, sizeof(inp)), server);
        //------------------------------------------

        //Получаем
        size_t len = socket.receive_from(asio::buffer(&pck, sizeof(pck)), sender, 0, ec);
        if (!ec && len == sizeof(pck)) {
            // Обновляем позиции
            bodies[0]->cor.x = pck.px;
            bodies[0]->cor.y = pck.py;
            bodies[0]->rotation = pck.rots[0];
            menu.stage = pck.stage;
            for (int i = 1; i < 51; ++i) {
                bodies[i]->cor.x = pck.cords[i * 2 - 2];
                bodies[i]->cor.y = pck.cords[i * 2 - 1];
                bodies[i]->rotation = pck.rots[i];
            }
        }
        //-------------------------------------



        //if (menu.stage != menu.MENU) {
        //    if (fl_pause) {
        //        if (!keyboard.isKeyPressed(keyboard.P)) {
        //            fl_pause = false;
        //        }


        //    }
        //    else {
        //        if (keyboard.isKeyPressed(keyboard.P)) {
        //            if (menu.stage == menu.PLAY) menu.stage = menu.PAUSE;
        //            else if (menu.stage == menu.PAUSE) menu.stage = menu.PLAY;
        //            fl = true;
        //        }
        //    }
        //}


        //if (menu.stage == menu.PLAY) {
        //    player.control();
        //    for (int i = 0; i < enemy.size(); ++i) {
        //        enemy[i].control();
        //    }
        //}
        //else if (menu.stage == menu.MENU) {
        //    for (int i = 0; i < menu.buttons.size(); ++i) {
        //        menu.buttons[i].isHover(window);
        //        if (fl) {
        //            if (!menu.buttons[i].isHover(window) && !mouse.isButtonPressed(mouse.Left)) {
        //                fl = false;
        //            }
        //            else if (!mouse.isButtonPressed(mouse.Left) && menu.buttons[i].isHover(window)) {
        //                menu.stage = menu.PLAY;
        //                fl = false;
        //            }

        //        }
        //        else {
        //            if (mouse.isButtonPressed(mouse.Left) && menu.buttons[i].isHover(window)) {
        //                fl = true;
        //            }
        //        }

        //    }
        //}

        //menu.stage = m;
        cam.control();
        cam.draw_all();

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