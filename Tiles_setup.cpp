#pragma once
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <fstream>
#include "boardsetup.h"
#include "Tiles_setup.h"
#include<vector>
using namespace  sf;
using namespace  std;

void Tiles::boardResetTile()  {
    this->setSprite("tile_hidden");
    this->tileReveal = false;
    mineSet = false;
    flagSet = false;
}

Tiles::Tiles() {
    tileReveal = false;
    flagSet = false;
    setSprite("tile_hidden");
    mineSet = false;

}
void Tiles::flagRemove() {
    this->flagSet=false;
}
bool Tiles::flagCheck() {
    if (this->flagSet) {
        return true;
    }

    else {
        return false;
    }
}

void Tiles::flagPlace() {
    this->flagSet = true;
}

void Tiles::revealPosofMine() {
    if (this != nullptr && this->neighborMines() == 0 && !this->mineSetCheck() && !this->flagCheck()) {
        for (int i = 0; i < 8; i++) {
            if (this->neighbors[i] != nullptr) {
                if (!this->neighbors[i]->RevealTile() && !this->neighbors[i]->mineSetCheck() && !this->flagCheck()) {
                    this->neighbors[i]->TileReveal();
                    if (this->neighbors[i]->neighborMines() == 0) {
                        this->neighbors[i]->revealPosofMine();
                    }
                }
            }
        }

    }
}
int Tiles::neighborMines()  {
    int num_mine = 0;
    for (int i = 0; i < 8; i++) {
        if (this->neighbors[i] != nullptr) {
            if (this->neighbors[i]->mineSetCheck())
                num_mine++;
        }
    }
    return num_mine;
}

bool Tiles::RevealTile()  {
    if (this->tileReveal) {
        return true;
    }
    return false;
}
bool Tiles::mineSetCheck() {
    if (this->mineSet) {
        return true;
    }
    else {
        return false;
    }
}

void Tiles::minePlace()  {
    this->mineSet = true;
}

void Tiles::TileReveal() {
    if (!this->flagCheck()) {
        this->setSprite("tile_revealed");
        this->tileReveal = true;
    }

}
sf::Sprite& Tiles::getSprite() {
    return this->tile;
}
void Tiles::setSprite(const char* name) {
    this->tile.setTexture(TxtManager::getTextureInfo(name));
}
void Tiles::setPosition(float pos_x, float pos_y)  {
    this->getSprite().setPosition(pos_x, pos_y);
}