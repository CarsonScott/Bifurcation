#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Tree.hpp"

class Game
{
public:
    void main(sf::RenderWindow& window)
    {
        srand(time(NULL));

        Tree tree(rand()%50 + 15);
        tree.setPosition(600, 800);

        float time_limit = 5;
        float time = 0;

        bool done = false;

        sf::Clock clock;
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            time += dt;
            if(time >= time_limit)
            {
                done = true;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    done = true;
                }
            }
            window.clear();

            if(done)
            {
                window.close();
            }

            tree.water(600*dt);
            tree.draw_branches(window);

            window.display();
        }
    }
};

int main()
{
    for(int i = 0; i < 8; i++)
    {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
        Game().main(window);
    }
    return 0;
}
