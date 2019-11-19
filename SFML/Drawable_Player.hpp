#ifndef DRAWABLE_PLAYER_H
#define DRAWABLE_PLAYER_H
#include<SFML/Graphics.hpp>
#include "Weapon.hpp"
#include "HpBar.hpp"
#include <map>
#include<iostream>
#include<sstream>
#include "player.hpp"

class Drawable_Player: public sf::Sprite, public player
{
public:
    Drawable_Player(std::string name,float x, float y, float a);
    virtual void setPosition(float x, float y);
    virtual void setRotation(float x);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
    sf::Texture getSkin();
    sf::Vector2<float> getPosition();
    virtual void setScale(float x, float y);
    virtual void setOrigin(float x, float y);

    //TODO
    std::map<std::string,Drawable_Player*> getPlayers();
    void setWeapon(int _weapon);
    void setCurrentHp(int _currentHp);
    void testPoke();

    //getters
    void update(std::string data);
    Weapon* getWeapon();
    ~Drawable_Player();
private:
    sf::Texture skin;
    sf::Sprite me;
    Weapon* myWeapon;
    HpBar* myHpBar;
    std::map<std::string,Drawable_Player*> players;
};

#endif // DRAWABLE_PLAYER_H
