#pragma once
#include "boardsetup.h"
#include <SFML/Graphics.hpp>

class ButtonSetup {
public:
    ButtonSetup(const char* name);
    sf::Sprite image;
    void setButtonSprite(const char* name);
    void setButtonPosition(float width, float height);
    sf::Sprite& getButtonSprite();
};


