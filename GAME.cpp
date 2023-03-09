// GAME.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
using namespace sf;
float speed = 0, angle = 0;
float maxSpeed = 3;
float acc = 0.2, dec = 0.3;
float turnSpeed = 0.06;
int offsetX = 30, offsetY = 30;
double dx, dy,rotation;
struct Tank
{
    double x, y, speed, angle; int n;

    Tank() { x = 90; y = 60; speed = 2; angle = 0; n = 0; }

    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }
};
class Bullet {
public:
    double mX, mY,speed;
    Texture bullet;
    Sprite Sbullet;
    Vector2f currVelocity;

    explicit Bullet(double x, double y):mX(x),mY(y)
    {
    bullet.loadFromFile("Bullet.png");
    bullet.setSmooth(true);
    Sbullet.setTexture(bullet);
    speed = 6;
    Sbullet.setScale(0.2, 0.2);
    Sbullet.setPosition(x,y);
    };
};

int main()
{
    sf::String TileMap[28] = {
        "000000000000000000000000000000",
        "00                          00",
        "00                          00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  000000  00  00  00",
        "00  00  00  000000  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00          00  00  00",
        "00  00  00          00  00  00",
        "00          00  00          00",
        "00          00  00          00",
        "0000  0000          0000  0000",
        "0000  0000          0000  0000",
        "00          00  00          00",
        "00          000000          00",
        "00  00  00  000000  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00  00  00  00  00  00",
        "00  00  00          00  00  00",
        "00  00  00          00  00  00",
        "00  00  00   0000   00  00  00",
        "00           0  0           00",
        "00           0  0           00",
        "000000000000000000000000000000",
    }
    ;

    sf::RenderWindow game(sf::VideoMode(900,740), "Tank game");
    game.setFramerateLimit(60);
    Texture  tank, turret, Background,wall;
    tank.loadFromFile("Tank.png");
    turret.loadFromFile("GunTurret.png");
    std::vector<Bullet> bullets;
    Vector2f TurretCenter;
    Background.loadFromFile("Stony wall.png");
    tank.setSmooth(true);
    wall.loadFromFile("Stony wall2.png");
    wall.setSmooth(true);
    Background.setSmooth(true);
    Sprite Stank(tank), Sturret(turret),SBackground(Background), Swall(wall);
    Swall.setScale(0.058, 0.058);
    std::vector<Sprite> Swalls;
    SBackground.scale(3, 3);
    Stank.scale(0.15, 0.15);
    Sturret.scale(0.15, 0.15);
    Tank ctank;
    Clock clock;
    bool isShoot=false;
    int map_x=0, map_y=0;
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < TileMap[i].getSize(); j++)
        {
            if (TileMap[i][j] == '0')
            {
                Swall.setPosition(map_x, map_y);
                Swalls.push_back(Swall);
            }
            map_x += 30;
        }
        map_x = 0;
        map_y +=30;
    }
    while (game.isOpen())
    {
        sf::Event event;
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game.close();
        }bool Up = 0, Right = 0, Down = 0, Left = 0;
        
       
        if (Keyboard::isKeyPressed(Keyboard::W)) Up = 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) Right = 1;
        if (Keyboard::isKeyPressed(Keyboard::S)) Down = 1;
        if (Keyboard::isKeyPressed(Keyboard::A)) Left = 1;
        if (Up && speed < maxSpeed)
            if (speed < 0)  speed += dec;
            else  speed += acc;

        if (Down && speed > -maxSpeed)
            if (speed > 0) speed -= dec;
            else  speed -= acc;

        if (!Up && !Down)
            if (speed - dec > 0) speed -= dec;
            else if (speed + dec < 0) speed += dec;
            else speed = 0;

        if (Right && speed != 0)  angle += turnSpeed * speed / maxSpeed;
        if (Left && speed != 0)   angle -= turnSpeed * speed / maxSpeed;
        ctank.speed = speed;
        ctank.angle = angle;
        Vector2f tank_lefttop(Stank.getGlobalBounds().left, Stank.getGlobalBounds().top);
        Vector2f tank_righttop(Stank.getGlobalBounds().left+ Stank.getGlobalBounds().width*sin(angle), Stank.getGlobalBounds().top-Stank.getGlobalBounds().width * cos(angle));
        Vector2f tank_leftbottom(Stank.getGlobalBounds().left -Stank.getGlobalBounds().height * sin(angle), Stank.getGlobalBounds().top -Stank.getGlobalBounds().height * cos(angle));
        Vector2f tank_rightbottom(tank_leftbottom.x + Stank.getGlobalBounds().width * cos(angle), tank_leftbottom.y + Stank.getGlobalBounds().width * cos(angle));
        for (int i = 0; i < Swalls.size(); i++)
        {
            if (Keyboard::isKeyPressed(Keyboard::W)&&Stank.getGlobalBounds().intersects(Swalls[i].getGlobalBounds())
               
               )
            {

                ctank.x -= sin(angle) * 1.5;
                ctank.y += cos(angle) * 1.5;
                speed = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::S) && Stank.getGlobalBounds().intersects(Swalls[i].getGlobalBounds())

                )
            {

                ctank.x += sin(angle) * 1.5;
                ctank.y -= cos(angle) * 1.5;
                speed = 0;
            }
        }
        ctank.move();
        game.clear();
        game.draw(SBackground);
        for (auto it = Swalls.begin(); it < Swalls.end(); it++)
        {
            game.draw(*it);
        }
        if (ctank.x > 320) offsetX = ctank.x - 320;
        if (ctank.y > 240) offsetY = ctank.y - 240;
        Stank.setOrigin(Stank.getLocalBounds().width / 2, Stank.getLocalBounds().height / 2);
        Stank.setPosition(ctank.x, ctank.y);
        Stank.setRotation(ctank.angle * 180 / 3.141593);
        game.draw(Stank);
        Sturret.setOrigin(Sturret.getLocalBounds().width/2, Sturret.getLocalBounds().height/1.2 ); 
        Sturret.setPosition(ctank.x, ctank.y);
        Vector2i mousepixelPos = Mouse::getPosition(game);
        Vector2f mousePosition = game.mapPixelToCoords(mousepixelPos);
        dx = mousePosition.x - Sturret.getPosition().x;
        dy = mousePosition.y - Sturret.getPosition().y;
        rotation= (atan2(dy, dx)) * 180 / 3.14159265;
        Sturret.setRotation(90+rotation);
        std::cout << 90+rotation<<"           "<<angle <<std::endl;
        TurretCenter.x =dx*0.1;
        TurretCenter.y = dy*0.1;
       game.draw(Sturret);
       if (clock.getElapsedTime().asSeconds() >= 3)
       {
           isShoot = true;
       }
        if (Mouse::isButtonPressed(Mouse::Left)&&isShoot)
        {
            clock.restart();
            isShoot = false;
            Bullet bullet(Sturret.getPosition().x, Sturret.getPosition().y);
            bullet.currVelocity.x = dx*bullet.speed / sqrt(pow(dx, 2) + pow(dy, 2));
            bullet.currVelocity.y = dy * bullet.speed / sqrt(pow(dx, 2) + pow(dy, 2));
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.move(bullet.currVelocity);
            bullet.Sbullet.setRotation(90+rotation);
            bullets.push_back(bullet);
            
        }   
        for (int i = 0; i < bullets.size(); i++)
        {

            bullets[i].Sbullet.move(bullets[i].currVelocity);
            if (bullets[i].Sbullet.getPosition().x<0 || bullets[i].Sbullet.getPosition().x>game.getSize().x
                || bullets[i].Sbullet.getPosition().y < 0 || bullets[i].Sbullet.getPosition().y>game.getSize().y)
            {
                bullets.erase(bullets.begin() + i);
            }
            for (int j = 0; j < Swalls.size(); j++)
            {
               
                if (bullets[i].Sbullet.getGlobalBounds().intersects(Swalls[j].getGlobalBounds()))
                {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            game.draw(bullets[i].Sbullet);
        }
        game.display();
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
