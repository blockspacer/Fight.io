#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
enum State
{
     main_menu=0,connecting,play
};
class Screen
{
protected:
    bool change;
 public:
     Screen() {change=false;};
     virtual void draw () =0;
     virtual void handle(sf::Event& event)=0;
     bool change_me() { return change;};
};

#endif // SCREEN_H