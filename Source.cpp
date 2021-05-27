#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include"Menu.h"

using namespace sf;
using namespace std;

int PageNumber;

int main()
{



    while (true)
    {
        RenderWindow window(VideoMode(608, 800), "Pacman!", Style::None);
        window.setFramerateLimit(60);
        menu menu(600, 800);

        //Textures
        Texture pacmanText, coin_1, menu_1, menu_2, maptexture, blinkyText, inkyText, clydeText, pinkieText,strawText;
        pacmanText.loadFromFile("Data/pacman spritesheet.png");

        coin_1.loadFromFile("Data/coin.png");
        coin_1.setSmooth(true);

        menu_1.loadFromFile("Data/menu.png");
        menu_1.setSmooth(true);

        menu_2.loadFromFile("Data/monsters.png");
        menu_2.setSmooth(true);

        maptexture.loadFromFile("Data/map.png");

        blinkyText.loadFromFile("Data/blinky.png");
        inkyText.loadFromFile("Data/inky.png");

        clydeText.loadFromFile("Data/clyde.png");

        pinkieText.loadFromFile("Data/pinkie.png");

        strawText.loadFromFile("Data/strawberry.png");

        Sprite pacman, mapsprite, blinky, inky, clyde, pinkie,strawberry;
        pacman.setTexture(pacmanText);
        pacman.setTextureRect(IntRect(0, 0, 30, 30));
        pacman.setOrigin(18, 18);
        pacman.setPosition(310, 500);
        pacman.setScale(0.9,0.9);


        mapsprite.setTexture(maptexture);


        blinky.setTexture(blinkyText);
        blinky.setScale(0.055, 0.055);
        blinky.setPosition(288, 288);

        inky.setTexture(inkyText);
        inky.setScale(0.016, 0.016);
        inky.setPosition(320, 415);

        clyde.setTexture(clydeText);
        clyde.setScale(0.060, 0.060);
        clyde.setPosition(255, 415);

        pinkie.setTexture(pinkieText);
        pinkie.setScale(0.060, 0.060);
        pinkie.setPosition(285, 380);

        strawberry.setTexture(strawText);
        strawberry.setScale(0.15, 0.15);

        CircleShape coin;
        coin.setPosition(Vector2f(400.0f, 200.0f));
        coin.setRadius(5);
        coin.setFillColor(Color::Yellow);

        RectangleShape menuText;
        menuText.setSize(Vector2f(600, 300));
        menuText.setPosition(Vector2f(10, 50));
        menuText.setTexture(&menu_1);

        RectangleShape menuText2;
        menuText2.setSize(Vector2f(400, 200));
        menuText2.setPosition(Vector2f(100, 200));
        menuText2.setTexture(&menu_2);




        //sounds
        SoundBuffer begginningBuff,eatingBuff;
        begginningBuff.loadFromFile("Data/beginning.wav");
        eatingBuff.loadFromFile("Data/eating.wav");
        Sound begginning,eating;
        begginning.setBuffer(begginningBuff);
        eating.setBuffer(eatingBuff);
        //begginning.play();

        


         //Variables
        int xVelocity = 0;
        int yVelocity = 0;
        
        int x = 0;
        int y = 0;
        int bx = 0;
        int by = 0;
        bool draw = true;
        bool right = false;
        bool left = false;
        bool up = false;
        bool down = false;
        int mapwidth = 19;
        int mapheight = 25;
        

        int map[25][19] = {
        {0 , 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
        {0 , 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0},
        {0 , 15,  0,  0, 15,  0,  0,  0, 15, 0, 15,  0,  0,  0, 15,  0,  0, 15, 0 },
        { 0 , 15, 15, 15, 17, 15, 15, 15, 15, 0, 15, 15, 15, 15, 17, 15, 15, 15, 0 },
        { 0 , 15,  0,  0, 15,  0,  0,  0, 15, 0, 15,  0,  0,  0, 15,  0,  0, 15, 0 },
        { 0 , 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,0},
        { 0 , 15,  0,  0, 15,  0, 15,  0,  0,  0,  0,  0, 15,  0, 15,  0,  0, 15,0},
        {0 , 15, 15, 15, 15,  0, 15, 15, 15,  0, 15, 15, 15,  0, 15, 15, 15, 15,0},
        {0 ,  0,  0,  0, 15,  0,  0,  0, 15,  0, 15,  0,  0,  0, 15,  0,  0,  0,0},
        {16 ,  16,  16,  0, 15, 0 , 15,  15,  15, 16,  15,  15, 15,  0, 15,  0,  16, 16 ,16},
        {0 ,  0,  0,  0, 15,  0, 15,  0,  0, 16,  0,  0, 15,  0, 15,  0,  0,  0,0},
        {15, 15, 15, 15, 15, 15, 15,  0, 16, 16, 16,  0, 15, 15, 15, 15, 15, 15, 15},
        {0 , 0 , 0 ,  0, 15, 0 , 15,  0, 16, 16,  16,  0, 15,  0, 15,  0, 0 , 0 ,0},
        {15, 15, 15, 15, 15, 15, 15,  0, 16, 16, 16,  0, 15, 15, 15, 15, 15, 15, 15},
        {0 , 0 , 0 ,  0, 15,  0, 15,  0,  0,  0,  0,  0, 15,  0, 15,  0,  0,  0,0},
        {16, 16, 16,  0, 15,  0, 15, 15, 15, 16, 15, 15, 15,  0, 15,  0, 16, 16, 16},
        {0 ,  0,  0,  0, 15,  0,  0,  0, 15,  0, 15,  0,  0,  0, 15,  0,  0,  0,0},
        {0 , 15, 15, 15, 15,  0, 15, 15, 15,  0, 15, 15, 15,  0, 15, 15, 15, 15,0},
        {0 , 15,  0,  0, 15,  0, 15,  0,  0,  0,  0,  0, 15,  0, 15,  0,  0, 15,0},
        {0 , 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,0},
        {0 , 15,  0,  0, 15,  0,  0,  0, 15,  0, 15,  0,  0,  0, 15,  0,  0, 15,0},
        {0 , 15, 15, 15, 17, 15, 15, 15, 15,  0, 15, 15, 15, 15, 17, 15, 15, 15,0},
        {0 , 15,  0,  0, 15,  0,  0,  0, 15, 0, 15,  0,  0,  0, 15,  0,  0, 15, 0},
        {0 , 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 0},
        {0 ,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0}

        };





        //Game Loop
        while (window.isOpen())
        {




            //Events
            Event event;

            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();



                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        menu.moveup();
                        break;
                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        menu.movedown();
                        break;

                    }

                    //Choosing a page
                    if (event.key.code == Keyboard::Return)
                    {
                        if (menu.MainMenuPressed() == 0)
                        {
                            window.close();
                            PageNumber = 0;
                        }
                        if (menu.MainMenuPressed() == 1)
                        {
                            window.close();
                            PageNumber = 1;
                        }
                        if (menu.MainMenuPressed() == 2)
                        {
                            window.close();
                            PageNumber = 2;
                        }
                    }

                }



            }

            window.clear();
            menu.draw(window);
            window.draw(menuText);
            window.draw(menuText2);
            window.display();




        }

        if (PageNumber == 0)
        {
            //play
            sf::RenderWindow play(sf::VideoMode(608, 800), "Play!", Style::None);
            play.setFramerateLimit(60);




            //Game Loop
            while (play.isOpen())
            {


                //Events
                sf::Event event;

                while (play.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        play.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        play.close();

                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Right && pacman.getPosition().x < 590)
                        {
                            right = true;
                            y = 0;
                            x++;
                            x = x % 7;
                            pacman.setTextureRect(IntRect(x * 32, y * 32, 30, 30));
                            if (pacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
                            {
                                draw = false;

                            }


                        }
                        else if (event.key.code == Keyboard::Left && pacman.getPosition().x > 20 || event.key.code == Keyboard::A && pacman.getPosition().x > 20)
                        {
                            left = true;
                            y = 2;
                            x++;
                            x = x % 7;
                            pacman.setTextureRect(IntRect(x * 32, y * 32, 30, 30));
                            if (pacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
                            {
                                draw = false;
                            }

                        }
                        else if (event.key.code == Keyboard::Up && pacman.getPosition().y > 20 || event.key.code == Keyboard::W && pacman.getPosition().y > 20)
                        {
                            up = true;
                            y = 3;
                            x++;
                            x = x % 7;
                            pacman.setTextureRect(IntRect(x * 32, y * 32, 30, 30));
                            if (pacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
                            {
                                draw = false;
                            }

                        }
                        else if (event.key.code == Keyboard::Down && pacman.getPosition().y < 785 || event.key.code == Keyboard::S && pacman.getPosition().y < 785)
                        {
                            down = true;
                            y = 1;
                            x++;
                            x = x % 7;

                            pacman.setTextureRect(IntRect(x * 32, y * 32, 30, 30));
                            if (pacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
                            {
                                draw = false;
                            }
                        }
                    }

                    if (event.type == Event::KeyReleased)
                    {
                        if (event.key.code == Keyboard::Right)
                            right = false;
                        if (event.key.code == Keyboard::Left)
                            left = false;
                        if (event.key.code == Keyboard::Up)
                            up = false;
                        if (event.key.code == Keyboard::Down)
                            down = false;
                    }



                }


                if (right)
                    xVelocity = 3;
                if (left)
                    xVelocity = -3;
                if (right && left)
                    xVelocity = 0;
                if (right == false && left == false)
                    xVelocity = 0;
                if (up)
                    yVelocity = -3;
                if (down)
                    yVelocity = 3;
                if (up && down)
                    yVelocity = 0;
                if (up == false && down == false)
                    yVelocity = 0;

                

                pacman.move(xVelocity, 0);
                pacman.move(0, yVelocity);


              if (blinky.getPosition().y > pacman.getPosition().y)
                {
                    by=-1;
                }
                if (blinky.getPosition().y < pacman.getPosition().y)
                {
                    by = 1;
                }
                if (blinky.getPosition().x > pacman.getPosition().x)
                {
                    bx = -1;
                }
                if (blinky.getPosition().x < pacman.getPosition().x)
                {
                    bx = 1;
                }
                blinky.move(bx, 0);
                blinky.move(0, by);
                if (inky.getPosition().y > blinky.getPosition().y)
                {
                    inky.move(Vector2f(0.0f, -0.4f));
                }
                if (inky.getPosition().y < blinky.getPosition().y)
                {
                    inky.move(Vector2f(0.0f, 0.4f));
                }
                if (inky.getPosition().x > blinky.getPosition().x)
                {
                    inky.move(Vector2f(-0.4f, 0.0f));
                }
                if (inky.getPosition().x < blinky.getPosition().x)
                {
                    inky.move(Vector2f(0.4f, 0.0f));
                }
                if (clyde.getPosition().y > blinky.getPosition().y)
                {
                    clyde.move(Vector2f(0.0f, -0.3f));
                }
                if (clyde.getPosition().y < blinky.getPosition().y)
                {
                    clyde.move(Vector2f(0.0f, 0.3f));
                }
                if (clyde.getPosition().x > blinky.getPosition().x)
                {
                    clyde.move(Vector2f(-0.3f, 0.0f));
                }
                if (clyde.getPosition().x < blinky.getPosition().x)
                {
                    clyde.move(Vector2f(0.3f, 0.0f));
                }
                if (pinkie.getPosition().y > blinky.getPosition().y)
                {
                    pinkie.move(Vector2f(0.0f, -0.2f));
                }
                if (pinkie.getPosition().y < blinky.getPosition().y)
                {
                    pinkie.move(Vector2f(0.0f, 0.2f));
                }
                if (pinkie.getPosition().x > blinky.getPosition().x)
                {
                    pinkie.move(Vector2f(-0.2f, 0.0f));
                }
                if (pinkie.getPosition().x < blinky.getPosition().x)
                {
                    pinkie.move(Vector2f(0.2f, 0.0f));
                }
              
                      /*  if (blinky.getPosition().x > mapsprite.getPosition().x)
                            bx=1;
                        if (blinky.getPosition().x < mapsprite.getPosition().x)
                            bx=-1;
                        if (blinky.getPosition().y > mapsprite.getPosition().y)
                            by=1;
                        if (blinky.getPosition().y < mapsprite.getPosition().y)
                            by=-1;
                       
                 
             
                 blinky.move(bx, 0);
                blinky.move(0, by);*/
                
                


                play.clear();
                for (int i = 0; i <= mapwidth; i++)
                {
                    for (int j = 0; j <= mapheight; j++)
                    {
                        if (map[j][i] == 0)
                        {
                            mapsprite.setPosition(i * 32.f, j * 32.f);
                            mapsprite.setTextureRect(IntRect(map[j][i] * 32, 0, 32, 32));
                            play.draw(mapsprite);
                            
                        }
                        if (map[j][i] == 15)
                        {

                            coin.setPosition(i * 32 + 14, j * 32 + 14);
                            play.draw(coin);
                        }
                        if (pacman.getGlobalBounds().intersects(mapsprite.getGlobalBounds()))
                        {
                            pacman.move(-xVelocity, 0);
                            pacman.move(0, -yVelocity);

                        }
                        if (blinky.getGlobalBounds().intersects(mapsprite.getGlobalBounds()))
                        {
                            blinky.move(-bx, 0);
                            blinky.move(0, -by);
                        }
                        if (map[j][i] == 17)
                        {
                            strawberry.setPosition(i * 32 +5 , j * 32 +5);
                            play.draw(strawberry);

                        }
                        if (map[j][i]==15)
                        {
                            if (pacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
                            {
                                map[j][i] = 18;
                               // eating.play();
                            }
                        }
                        if (map[j][i] == 17)
                        {
                            if (pacman.getGlobalBounds().intersects(strawberry.getGlobalBounds()))
                            {
                                map[j][i] = 18;
                                // eating.play();
                            }
                        }
                       /* if (map[j][i] == 18)
                        {
                            
                            blinky.move(bx, 0);
                        blinky.move(0, by);
                        }*/
                        
                    }
                }
                
                play.draw(pacman);
                play.draw(blinky);
                play.draw(inky);
                play.draw(clyde);
                play.draw(pinkie);
                play.display();



            }
        }
        if (PageNumber == 1)
        {
            //Controls
            sf::RenderWindow controls(sf::VideoMode(608, 800), "Controls", Style::None);
            controls.setFramerateLimit(60);

            //Game Loop
            while (controls.isOpen())
            {
                //Events
                sf::Event event;

                while (controls.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        controls.close();
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        controls.close();


                }

                controls.clear();
                controls.display();
            }

        }
        if (PageNumber == 2)
        {
            //exit
            break;

        }











    }



    return 0;
}