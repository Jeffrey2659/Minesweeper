#include <iostream>
#include "board.h"
#include <cctype>
using namespace std;
#include <string>
using namespace sf;
#include <SFML/Graphics.hpp>

float one = 0.0f;
Board::Board() {
    playGame= true;
    debugState = false; // parent cosntructor
    setPause = false;
    timeRun =true;

}
void Board::setTilePostion(Tiles (&ptile)[16][25]) {

    float y = 0.0f;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            ptile[i][j].setPosition(one, y);
            one += 32.0f;
        }
        one = 0;
        y += 32.0f;
    }
}
void Board::setBoardCreate(vector<MinewithFlag> &flagin, RenderWindow &window, vector<numofMines>& numMine, vector<flagcount>& flagcount,
                           vector<ButtonSetup>& button, bool playGame, vector<setMine> &, bool debugState, Tiles (&ptile)[16][25],
                           setMine (&pmin)[50],int sec1,int sec10, int min1, int min10) {
    int index = 0;
        if (playGame) {
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {
                    index = minesetPostion(ptile[i][j], pmin);
                    if (index != -1 && ptile[i][j].RevealTile()) {
                        window.draw(ptile[i][j].getSprite());
                        window.draw(pmin[index].getSprite());

                    } else {
                        window.draw(ptile[i][j].getSprite());
                        for (int k = 0; k < numMine.size(); k++) {
                            if (ptile[i][j].RevealTile()) {
                                if (numMine[k].tile.getPosition().x == ptile[i][j].tile.getPosition().x &&
                                    numMine[k].tile.getPosition().y == ptile[i][j].tile.getPosition().y) {
                                    window.draw(numMine[k].getSprite());
                                }
                            }
                        }
                    }
                }
            }
            if (winCheck(ptile, flagin, pmin)) {
                timeRun = false;
                window.draw(button[2].getButtonSprite());
            }
            if (!winCheck(ptile, flagin, pmin)) {
                window.draw(button[0].getButtonSprite());
            }

        }


        if ((!playGame || debugState)) {
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {
                    index = minesetPostion(ptile[i][j], pmin);
                    if (index != -1) {
                        window.draw(ptile[i][j].getSprite());
                        window.draw(pmin[index].getSprite());
                    } else {
                        window.draw(ptile[i][j].getSprite());
                        for (int k = 0; k < numMine.size(); k++) {
                            if (ptile[i][j].RevealTile()) {
                                if (numMine[k].tile.getPosition().x == ptile[i][j].tile.getPosition().x &&
                                    numMine[k].tile.getPosition().y == ptile[i][j].tile.getPosition().y) {
                                    window.draw(numMine[k].getSprite());
                                }
                            }
                        }
                    }
                }
            }
            if (!playGame)
                window.draw(button[1].getButtonSprite());
            if (winCheck(ptile, flagin, pmin)) {
                timeRun = false;
                window.draw(button[2].getButtonSprite());
            }

        }

    for (int i = 0; i < flagin.size(); i++) {
        window.draw(flagin[i].getSprite());
    }

    if (flagin.size() <= 50) {    //flags size

        index = 50 - flagin.size();
        flagcount[index % 10].setPosition(42, 512);
        window.draw(flagcount[index % 10].getSprite());
        flagcount[0].setPosition(0, 512);
        window.draw(flagcount[0].getSprite());
        flagcount[index / 10].setPosition(21, 512);
        window.draw(flagcount[index / 10].getSprite());
    }
    else if (flagin.size() > 50) {
        flagcount[10].setPosition(0, 512);
        window.draw(flagcount[10].getSprite());
        index = flagin.size() - 50;
        if (index >= 100) {
            flagcount[index / 100].setPosition(21, 512);
            window.draw(flagcount[index / 100].getSprite());
            flagcount[(index / 10) % 10].setPosition(42, 512);
            window.draw(flagcount[(index / 10) % 10].getSprite());
            flagcount[index % 10].setPosition(63, 512);
            window.draw(flagcount[index % 10].getSprite());

        }
        else {
            flagcount[0].setPosition(21, 512);
            window.draw(flagcount[0].getSprite());
            flagcount[index / 10].setPosition(42, 512);
            window.draw(flagcount[index / 10].getSprite());

            flagcount[index % 10].setPosition(63, 512);
            window.draw(flagcount[index % 10].getSprite());
        }
    }


    if(playGame && timeRun){
        flagcount[min10].setPosition(703,512);
        window.draw(flagcount[min10].getSprite());
        flagcount[min1].setPosition(724,512);
        window.draw(flagcount[min1].getSprite());
        flagcount[sec10].setPosition(745,512);
        window.draw(flagcount[sec10].getSprite());
        flagcount[sec1].setPosition(766,512);
        window.draw(flagcount[sec1].getSprite());
    }
    if(playGame && setPause){

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
              ptile[i][j].setSprite("tile_revealed");
               window.draw(ptile[i][j].getSprite());
            }
        }
    }






    window.draw(button[3].getButtonSprite());
    window.draw(button[4].getButtonSprite());
    window.draw(button[5].getButtonSprite());
}
void Board ::boardCreate(setMine (&pmin)[50], vector<MinewithFlag> & flagin, Tiles (&ptile)[16][25], vector<numofMines> &numMine ) {
    numMine.clear();
    flagin.clear();
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            ptile[i][j].boardResetTile();

        }
    }
    launchMine(ptile,pmin);
    setmineNum(numMine,ptile);
    startMinesweeper();
}
void Board::setmineNum(vector<numofMines>  &numMine, Tiles (&ptile)[16][25])  {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            count = ptile[i][j].neighborMines();
            if (count != 0) {
                if (!ptile[i][j].mineSetCheck()) {
                    numofMines val(count);
                    val.setPosition(ptile[i][j].tile.getPosition().x, ptile[i][j].tile.getPosition().y);
                    numMine.push_back(val);
                }
            }
        }
    }
}
void Board::launchMine(Tiles (&ptile)[16][25], setMine (&pmin)[50])  {
    vector<int> vectx;
    vector<int> vecty;
    for (int i = 0; i < 50; i++) {
        int height = Random::mineAmount(0, 15);
        vecty.push_back(height);
        int width = Random::mineAmount(0, 24);
        vectx.push_back(width);
    }
    if (mineSelection(vectx,vecty)) {
        vectx.clear();
        vecty.clear();
        launchMine(ptile, pmin);
    }
    else {
        for (int i = 0; i < 50; i++) {
            pmin[i].setPosition(ptile[vecty[i]][vectx[i]].tile.getPosition().x, ptile[vecty[i]][vectx[i]].tile.getPosition().y);
            ptile[vecty[i]][vectx[i]].minePlace();
        }
    }
}
int Board::minesetPostion(Tiles (&ptile), setMine (&pmin)[50])  {
    for (int i = 0; i < 50; i++) {
        if (ptile.tile.getPosition().x == pmin[i].tile.getPosition().x && ptile.tile.getPosition().y == pmin[i].tile.getPosition().y) {
            return i;
        }
    }
    return -1;
}
int Board::checkMinePosition(Tiles (&ptile), vector<setMine>& setMines)  {
    for (int i = 0; i < setMines.size(); i++) {
        if (ptile.tile.getPosition().x == setMines[i].tile.getPosition().x && ptile.tile.getPosition().y == setMines[i].tile.getPosition().y) {
            return i;
        }
    }
    return -1;
}
bool Board::mineSelection(vector<int> &width_rand, vector<int> &height_rand)  {
    for (int i = 0; i < height_rand.size(); i++) {
        for (int j = i + 1; j < height_rand.size(); j++) {
            if (height_rand[i] == height_rand[j] && i != j) {
                if (width_rand[i] == width_rand[j]) {
                    return true;
                }
            }
        }
    }
    return false;
}
void Board::connectTiles(Tiles (&ptile)[16][25])  {

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (i == 0) {
                ptile[i][j].neighbors[0] = nullptr;
                ptile[i][j].neighbors[1] = nullptr;
                ptile[i][j].neighbors[7] = nullptr;
                if (j == 0) {
                    ptile[i][j].neighbors[2] = &ptile[0][1];
                    ptile[i][j].neighbors[3] = &ptile[1][1];
                    ptile[i][j].neighbors[4] = &ptile[1][0];
                    ptile[i][j].neighbors[5] = nullptr;
                    ptile[i][j].neighbors[6] = nullptr;
                }
                if (j != 0 && j != 24) {
                    ptile[i][j].neighbors[2] = &ptile[i][j + 1];
                    ptile[i][j].neighbors[3] = &ptile[i + 1][j + 1];
                    ptile[i][j].neighbors[4] = &ptile[i + 1][j];
                    ptile[i][j].neighbors[5] = &ptile[i + 1][j - 1];
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                }
                if (j == 24) {
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                    ptile[i][j].neighbors[5] = &ptile[i + 1][j - 1];
                    ptile[i][j].neighbors[4] = &ptile[i + 1][j];
                    ptile[i][j].neighbors[2] = nullptr;
                    ptile[i][j].neighbors[3] = nullptr;
                }
            }
            else if (i != 0 && i != 15) {
                if (j == 0) {
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[1] = &ptile[i - 1][j + 1];
                    ptile[i][j].neighbors[2] = &ptile[i][j + 1];
                    ptile[i][j].neighbors[3] = &ptile[i + 1][j + 1];
                    ptile[i][j].neighbors[4] = &ptile[i + 1][j];
                    ptile[i][j].neighbors[5] = nullptr;
                    ptile[i][j].neighbors[6] = nullptr;
                    ptile[i][j].neighbors[7] = nullptr;
                }
                else if (j == 24) {
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[1] = nullptr;
                    ptile[i][j].neighbors[2] = nullptr;
                    ptile[i][j].neighbors[3] = nullptr;
                    ptile[i][j].neighbors[4] = &ptile[i + 1][j];
                    ptile[i][j].neighbors[5] = &ptile[i + 1][j - 1];
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                    ptile[i][j].neighbors[7] = &ptile[i - 1][j - 1];
                }
                else if (j != 0 && j != 24) {
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[1] = &ptile[i - 1][j + 1];
                    ptile[i][j].neighbors[2] = &ptile[i][j + 1];
                    ptile[i][j].neighbors[3] = &ptile[i + 1][j + 1];
                    ptile[i][j].neighbors[4] = &ptile[i + 1][j];
                    ptile[i][j].neighbors[5] = &ptile[i + 1][j - 1];
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                    ptile[i][j].neighbors[7] = &ptile[i - 1][j - 1];
                }
            }
            else if (i == 15) {
                ptile[i][j].neighbors[3] = nullptr;
                ptile[i][j].neighbors[4] = nullptr;
                ptile[i][j].neighbors[5] = nullptr;
                if (j == 0) {
                    ptile[i][j].neighbors[2] = &ptile[i][j + 1];
                    ptile[i][j].neighbors[1] = &ptile[i - 1][j + 1];
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[6] = nullptr;
                    ptile[i][j].neighbors[7] = nullptr;
                }
                if (j != 0 && j != 24) {
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[1] = &ptile[i - 1][j + 1];
                    ptile[i][j].neighbors[2] = &ptile[i][j + 1];
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                    ptile[i][j].neighbors[7] = &ptile[i - 1][j - 1];

                }
                if (j == 24) {
                    ptile[i][j].neighbors[0] = &ptile[i - 1][j];
                    ptile[i][j].neighbors[7] = &ptile[i - 1][j - 1];
                    ptile[i][j].neighbors[6] = &ptile[i][j - 1];
                    ptile[i][j].neighbors[2] = nullptr;
                    ptile[i][j].neighbors[1] = nullptr;
                }
            }
        }
    }
}
void Board::placeFlag(vector<MinewithFlag> &flagvect, Tiles (&ptile))  {
    MinewithFlag flags;
    flags.setPosition(ptile.tile.getPosition().x, ptile.tile.getPosition().y);
    flagvect.push_back(flags);
    ptile.flagPlace();
}
void Board::removeFlag(Tiles (&ptile), vector<MinewithFlag> & flagin)  {
    for (int i = 0; i < flagin.size(); i++) {
        if (flagin[i].tile.getPosition().x == ptile.tile.getPosition().x && flagin[i].tile.getPosition().y == ptile.tile.getPosition().y) {
            flagin.erase(flagin.begin() + i);

        }
    }
    ptile.flagRemove();
}
void Board::setflagCounter(vector<flagcount> &flagcout)  {
    for (int i = 0; i <= 10; i++) {
        flagcount val(i);
        flagcout.push_back(val);
    }
}

void Board::buttonCreate(vector<ButtonSetup>& buttonhold)  {

    ButtonSetup sprite1("face_happy");
    sprite1.setButtonPosition(368, 512);
    ButtonSetup sprite2("face_lose");
    sprite2.setButtonPosition(368, 512);
    ButtonSetup sprite3("face_win");
    sprite3.setButtonPosition(368, 512);
    ButtonSetup sprite4("debug");
    sprite4.setButtonPosition(496, 512);
    ButtonSetup sprite5("pause");
    sprite5.setButtonPosition(560, 512);
    ButtonSetup sprite6("leaderboard");
    sprite6.setButtonPosition(624, 512);
    /*Button g("test_3");
    g.setPosition(688, 512);*/
    buttonhold.push_back(sprite1);
    buttonhold.push_back(sprite2);
    buttonhold.push_back(sprite3);
    buttonhold.push_back(sprite4);
    buttonhold.push_back(sprite5);
    buttonhold.push_back(sprite6);

}
void Board::startMinesweeper()  {
    this->playGame = true;
}
void Board::endMinesweeper() {
    this->playGame = false;
}
bool Board::updateBoard() {
    return this->playGame;
}
void Board::loadDebugger(bool truthval)  {
    this->debugState = truthval;
}
bool Board::getDebugMode() {
    return this->debugState;
}

bool Board::winCheck(Tiles (&ptile)[16][25], vector<MinewithFlag> &flagin, setMine (&pmin)[50])  {
    int gameMines = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (ptile[i][j].RevealTile() && minesetPostion(ptile[i][j], pmin) == -1) {
                gameMines++;
            }
        }
    }
    if (gameMines == 350) {
        flagin.clear();
        for (int i = 0; i < 50; i++) {
            MinewithFlag flagmine;
            flagmine.setPosition(pmin[i].getSprite().getPosition().x, pmin[i].getSprite().getPosition().y);
            flagin.push_back(flagmine);
        }
        return true;
    }
    else {
        return false;
    }
}

void Board::loadtimeRun(bool sec) {
     this->timeRun = sec;
}

bool Board::getPause() {
    return this->setPause;
}

void Board::loadPause(bool val) {
    this->setPause=val;
}



