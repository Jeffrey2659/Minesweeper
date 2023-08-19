
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace  sf;
using namespace  std;

struct GameWindow {
    Texture texture;
    Sprite board_tile;
    int width;
    int height;
    int tileCount;
    int num_mines;

    vector<vector<Sprite>> tiles_;
    GameWindow(){ }
    GameWindow(string filename){
        texture.loadFromFile(filename);
        board_tile.setTexture(texture);
    }


    void drawtoScreen(RenderWindow &window){
        window.draw(board_tile);
    }

    void height_width(ifstream &inFS){


        inFS >> width>>height>>tileCount ;
        width = width *32;
        height= (height *32)+100;
        tileCount= tileCount * height;

    }












};



