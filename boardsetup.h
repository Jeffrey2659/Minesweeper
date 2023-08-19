#pragma once
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <string>
using namespace  sf;
using namespace  std;


class TxtManager{

    static unordered_map<string, Texture> textures;
    static void LoadTexture(const char* fileName);


public:
    static Texture& getTextureInfo(const char* name_);
    static void Clear();

};

