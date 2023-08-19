#pragma once
#include <vector>
#include <iterator>
#include "Tiles_setup.h"
#include "setMine.h"
#include "flagcount.h"
#include "ButtonSetup.h"

#include "Random.h"
#include <iostream>
#include <string>
#include "TileLabels.h"
//#include "timeCounter.h"
#include "MinewithFlag.h"
#include <fstream>

#include <SFML/Graphics.hpp>
using namespace std;
using namespace  sf;

class Board {
    bool setPause;
    bool playGame;
    bool debugState;
    bool timeRun;


public:
    Board();

    void loadtimeRun(bool);
    void loadPause(bool);
    bool getPause();
    void buttonCreate(vector<ButtonSetup>&);
    void setflagCounter(vector<flagcount>&);
    void setTilePostion(Tiles(&ptile)[16][25]);
    void startMinesweeper();
    void setmineNum(vector<numofMines>&,Tiles(&ptile)[16][25]);
    void endMinesweeper();
    bool winCheck(Tiles(&ptile)[16][25],vector<MinewithFlag>&,setMine(&pmin)[50]);
    bool getDebugMode();
    void connectTiles(Tiles(&ptile)[16][25]);
    int minesetPostion(Tiles(&ptile),setMine(&pmin)[50]);
    int checkMinePosition(Tiles(&ptile),vector<setMine>&);
    bool updateBoard();
    void placeFlag(vector<MinewithFlag>&,Tiles(&ptile));
    void removeFlag(Tiles(&ptile),vector<MinewithFlag>&);
    void boardCreate(setMine(&pmin)[50],vector<MinewithFlag> &, Tiles(&ptile)[16][25], vector<numofMines> &);
    void loadDebugger(bool);
    void launchMine(Tiles(&ptile)[16][25],setMine(&pmin)[50]);
    bool mineSelection(vector<int>& width_rand,vector<int>& height_rand);
    void setBoardCreate(vector<MinewithFlag>&,RenderWindow& window,vector<numofMines>&,vector<flagcount>&,vector<ButtonSetup>&,bool,vector<setMine>&,bool,Tiles(&ptile)[16][25],setMine(&pmin)[50],int ,int ,int ,int);






};