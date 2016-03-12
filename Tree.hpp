#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

class Tree:public sf::RectangleShape
{
    float base, height, growth_limit, angle;
    std::vector<Tree> branches;

    void bifurcate()
    {
        float pos_x = getGlobalBounds().left;
        float pos_y = getGlobalBounds().top - height;

        if(angle > 0)
        {
            pos_x += getGlobalBounds().width;
        }

        float left_angle = angle - rand()%45;
        Tree* left = new Tree(base*.75, left_angle);

        sf::Vector2f l_pos;
        l_pos.x = pos_x;
        l_pos.y = pos_y + height;
        left->setPosition(l_pos);

        branches.push_back(*left);

        float right_angle = angle + rand()%45;
        Tree* right = new Tree(base*.75, right_angle);

        sf::Vector2f r_pos;
        r_pos.x = pos_x;
        r_pos.y = pos_y + height;
        right->setPosition(r_pos);

        branches.push_back(*right);
    }
public:
    Tree(float base, float angle=0)
    {
        this->base = base;
        height = sqrt(base);

        growth_limit = base*5;

        sf::Vector2f origin;
        origin.x = base/2;
        origin.y = 0;
        setOrigin(origin);

        this->angle = angle;
        setRotation(angle);

        setFillColor(sf::Color::White);
    }

    void water(float energy)
    {
        if(height < growth_limit)
        {
            height += energy;
            if(height >= growth_limit)
            {
                height = growth_limit;
                bifurcate();
            }

            setSize(sf::Vector2f(base, -height));
        }

        for(int i = 0; i < branches.size(); i++)
        {
            branches[i].water(energy/1.5);
        }
    }

    void draw_branches(sf::RenderWindow& window)
    {
        window.draw(*this);
        for(int i = 0; i < branches.size(); i++)
        {
            branches[i].draw_branches(window);
        }
    }
};

#endif // TREE_HPP_INCLUDED
