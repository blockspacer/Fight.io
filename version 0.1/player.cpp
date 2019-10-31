# include "player.hpp"
#include <sstream>
#include <string>
#include <iostream>

//constructors************************************************
/*
player::player()
{
    maxHp =  100;
    currentHp = maxHp;
    score = 0;
    weapon = false;
}*/
player::player(std::string _pName)
{
    playerX=0;
    playerY=0;
    playerRotation=0;
    pName = _pName;
    maxHp =  100;
    currentHp = maxHp;
    score = 0;
    //weapon = false;
    w=new Weapon(30,30);
    myPlayer=new Drawable_Player(this);
    myPlayer->get().setScale(0.5f,0.5f);
    myPlayer->get().setOrigin(myPlayer->getSkin().getSize().x/2, myPlayer->getSkin().getSize().y/2);
    w->setPosition(myPlayer->get().getPosition());
    w->setOrigin(-((int)myPlayer->getSkin().getSize().x/2), (w->skin.getSize().y/2)+50);

}
/*
player::player(std::string _pName, float _playerX, float _playerY, float _playerRotation, sf::Texture& playerTexture)
{
    playerX = _playerX;
    playerY = _playerY;
    playerRotation = _playerRotation;
    pName = _pName;
    maxHp =  100;
    currentHp = maxHp;
    score = 0;
    weapon = false;
    myPlayer->get().setScale(sf::Vector2f(0.5f, 0.5f));
    myPlayer->get().setOrigin(playerTexture.getSize().x/2, playerTexture.getSize().y/2);
    myPlayer->get().setPosition(_playerX,_playerY); // todo
    myPlayer->get().setTexture(playerTexture);
}
/*player::player(float _playerX, float _playerY, float _playerRotation,
                std::string _pName, int _maxHp, int _currentHp, int _score, bool _weapon)
                : playerX(_playerX), playerY(_playerY), playerRotation(_playerRotation),
                pName(_pName), maxHp(_maxHp), currentHp(_currentHp), score(_score), weapon(_weapon) {}*/

//setters************************************************

void player::setPosition(float _playerX, float _playerY)
{
    playerX = _playerX;
    playerY = _playerY;
    myPlayer->get().setPosition(playerX,playerY);
    w->setPosition(myPlayer->get().getPosition());
}
void player::setRotation(float _playerRotation)
{
    playerRotation = _playerRotation;
    myPlayer->get().setRotation(_playerRotation);
    w->setRotation(myPlayer->get().getRotation());
}
void player::setPName(std::string _pName)
{
    pName = _pName;
}
void player::setMaxHp(int _maxHp)
{
    maxHp = _maxHp;
}
void player::setCurrentHp(int _currentHp)
{
    if(_currentHp <= maxHp)
        currentHp = _currentHp;
}
void player::setScore(int _score)
{
    score = _score;
}
//false is the default value (no weapon)
void player::setWeapon(Weapon* _weapon)
{
    w = _weapon;
}

//getters************************************************

float player::getX()
{
    return myPlayer->get().getPosition().x;
}
float player::getY()
{
    return myPlayer->get().getPosition().y;
}
float player::getRot()
{
    return playerRotation;
}
std::string player::getName()
{
    return pName;
}
int player::getMaxHp()
{
    return maxHp;
}
int player::getCurrentHp()
{
    return currentHp;
}
int player::getScore()
{
    return score;
}
Weapon* player::getWeapon()
{
    return w;
}
sf::Sprite& player::getSprite()
{
    return myPlayer->get();
}

std::string player::getMSG()
{
    //std::cout << myPlayer.getPosition().x << " " << myPlayer.getPosition().y << std::endl;
    std::stringstream s;
    my_mutex.lock();
    s << myPlayer->get().getPosition().x << "|" << myPlayer->get().getPosition().y << "|" << myPlayer->get().getRotation();
my_mutex.unlock();
    return s.str();
}

std::string player::toString() {
    std::stringstream s;
    s << "X: " << getX() << " Y: " << getY() << " R: " << getRot()
        << " PName: " << getName() << " maxHP: " << getMaxHp() << " currentHP: " << getCurrentHp()
        << " Score: " << getScore() << " Weapon: " << getWeapon();
    return s.str();
}
void player::update(std::string data)
{
    if(data.find("Your Name:")!=std::string::npos)
        {
            std::cout<<" NEW NAME!!! "<<std::endl;
            pName = data.substr(10, data.length()-1);
            players.insert(std::pair<std::string, player*>(pName,this));
        }
    else if(data.find("|")!=std::string::npos)
    {
        std::cout<<" NEW DATA "<<std::endl;
        std::cout<<data<<std::endl;
        std::stringstream ss(data);
        std::string currentName;
        std::getline(ss,currentName,':');
        std::string line;
        std::getline(ss,line,'|');
        float curx = std::stof(line);
        std::getline(ss,line,'|');
        float cury = std::stof(line);
        std::getline(ss,line,'|');
        float getrot = std::stof(line);
        my_mutex.lock();
        if(players.find(currentName)== players.end())
        {
            players[currentName] = new player(currentName);
        }
        players[currentName]->setPosition(curx,cury);
        players[currentName]->setRotation(getrot);

    }
    my_mutex.unlock();
}
std::map<std::string,player*> player::getPlayers()
{
    my_mutex.lock();
    std::map<std::string,player*> result(players);
    my_mutex.unlock();
    return result;
}
player::Drawable_Player::~Drawable_Player()
{
    delete player;
}
sf::Sprite& player::Drawable_Player::get()
{
    return player::Drawable_Player::me;
}