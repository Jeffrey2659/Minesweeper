#pragma once
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>
#include <fstream>
#include "boardsetup.h"
#include<vector>
using namespace  sf;
using namespace  std;


class Tiles {
    bool flagSet;
    bool mineSet;
    bool tileReveal;
public:

    Tiles* neighbors[8];
    Tiles();
    bool mineSetCheck();
    void minePlace();
    void boardResetTile();
    Sprite tile;
    bool flagCheck();
    void flagPlace();
    void flagRemove();
    int neighborMines();
    Sprite& getSprite();
    bool RevealTile();
    void revealPosofMine();
    void TileReveal();
    void setPosition(float pos_x,float pos_y);
    void setSprite(const char* spriteName);
    float width;
    float height;
    float mineCount;
    float tileCount;
    float width_edit;
    float height_edit;



    void height_width(ifstream &inFS){


        inFS >> width>>height>>mineCount ;
        /*tileWidth= width;
        tileHeight=height;*/
        //tileCount= width * height;
        width_edit= width*32;
        height_edit= (height *32)+100;
        tileCount=height*width;

    }





};



















/*vector<vector<Tiles>> tiles;
    //vector<vector<Sprite>> tiles_;
    Tiles* neighbors[8];
    int position_x;
    int position_y;
    Texture texture;
    Sprite tiles_sprite;
    int width;
    int height;
    int width_edit;
    int  height_edit;
    int tileCount;
    bool isRevealed = false;
    bool isMine = false;
    bool isFlag =false;
    *//*int tileWidth;
    int tileHeight;*//*
    Board board;
    Tiles(){

    }
    *//*Tiles(string filename){
       //board.tile_reveal;
        texture.loadFromFile(filename);
        board_tile.setTexture(texture);
    }*//*
    Tiles( Sprite tiles_sprite, float position_x,float position_y){
        this->tiles_sprite= tiles_sprite;
        this->position_x=position_x;
        this->position_y=position_y;
        //board.tile_hidden.setPosition(position_x,position_y);
    }
    void tile_pushback(){

        for(int i=0; i<height; i++)
        {   vector<Tiles> inner_tiles;

            for(int j=0; j<width; j++)
            {   Tiles t(board.tile_hidden,i*32.0f,j*32.0f);
                inner_tiles.push_back(t);
            }
                tiles.push_back(inner_tiles);
        }
    }


    void drawtoScreen(RenderWindow &window){
        *//*if(isRevealed==true){
            window.draw(board.tile_reveal);
        }if(isRevealed==false){
            window.draw(board.tile_hidden);
        }*//*
        for(int i =0; i < tiles.size();i++){
            for(int j=0;j <tiles[i].size();j++){
                tiles[i][j].tiles_sprite.setPosition(tiles[i][j].position_x,tiles[i][j].position_y);
                window.draw(tiles[i][j].tiles_sprite);
            }
        }
    }
    *//*void loadTexture(string filename){
        texture.loadFromFile(filename);
    }*/