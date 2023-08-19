
#include "boardsetup.h"
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <string>
using namespace  sf;
using namespace  std;

// from professor foxes lecture on this topic credit to him
std::unordered_map<std::string, sf::Texture> TxtManager::textures;
void TxtManager::LoadTexture(const char* fileName) {
    string filePath = "../images/";
    filePath += fileName;
    filePath += ".png";
    textures[fileName].loadFromFile(filePath);
}
sf::Texture& TxtManager::getTextureInfo(const char* name) {
    if (textures.find(name) == textures.end()) {
        LoadTexture(name);
    }
    return textures[name];
}
void TxtManager::Clear() {
    textures.clear();
}
