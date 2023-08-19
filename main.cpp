
#include <SFML/Graphics.hpp>
#include <cctype>

#include "open_window.h"
#include "gamewindow.h"

#include "flagcount.h"
#include "Tiles_setup.h"
#include "MinewithFlag.h"
#include "setMine.h"
#include "board.h"
#include "boardsetup.h"
#include "Tiles_setup.h"
#include <iostream>
#include "Random.h"
#include <fstream>
using namespace  sf;
using namespace  std;




int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML window", sf::Style::Close);
    Event event;
    Font font;
    Text text_main;
    Text text_input_prompt;
    //Welcome to MineSweeper text
    font.loadFromFile("../minesweeper/files/font.ttf");
    text_main.setFont(font);
    text_main.setString("WELCOME TO MINESWEEPER!");
    text_main.setCharacterSize(24);
    text_main.setStyle(Text::Bold | Text::Underlined);
    text_main.setFillColor(Color::White);
    FloatRect  textRect = text_main.getLocalBounds();
    text_main.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text_main.setPosition(sf::Vector2f(800.0f/2.0f,600.0f/2.0f-150));
    // input prompt text
    text_input_prompt.setFont(font);
    text_input_prompt.setString("Enter your name:");
    text_input_prompt.setCharacterSize(20);
    text_input_prompt.setStyle(Text::Bold );
    text_input_prompt.setFillColor(Color::White);
    FloatRect  textRect_prompt = text_input_prompt.getLocalBounds();
    text_input_prompt.setOrigin(textRect_prompt.left + textRect_prompt.width/2.0f,
                        textRect_prompt.top  + textRect_prompt.height/2.0f);
    text_input_prompt.setPosition(sf::Vector2f(800.0f/2.0f,600.0f/2.0f-75));
    // response text

    Textbox textbox1(18, Color::Yellow, true);
    textbox1.setFont(font);
    textbox1.setPosition({800.0f/2.0f,600.0f/2.0f-45});
    textbox1.setLimit(true,10);

    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){
                window.close();
            }
            if(event.type==Event::TextEntered){
                textbox1.typeInput(event);

            }
        }
        window.clear(Color::Blue);
        window.draw(text_main);
        window.draw(text_input_prompt);
        textbox1.drawtoScreen(window);
        window.display();
    }

    ifstream inFS;
    inFS.open("/files/board_config.cfg");
    Tiles obj;
    obj.height_width(inFS);
    RenderWindow gamewindow(VideoMode(800, 600), "SFML window", sf::Style::Close);


    Board mine_board;
    Clock clock;
    Time time;
    Tiles all_tiles[16][25];
    setMine all_mines[50];
    vector<setMine> totmine_vect;
    vector<numofMines> numtot_mines;
    vector<MinewithFlag> flaggedmines;
    vector<flagcount> minecount_tot;
    vector<ButtonSetup> sprite_buttons;
    mine_board.buttonCreate(sprite_buttons);
    mine_board.setflagCounter(minecount_tot);
    mine_board.setTilePostion(all_tiles);
    mine_board.connectTiles(all_tiles);
    mine_board.launchMine(all_tiles,all_mines);
    mine_board.setmineNum(numtot_mines,all_tiles);
    int minutes=0;
    int seconds=0;
    int timeNow=0;
    int minin1place;
    int minin10place;
    int secondin1place;
    int secondin10place;

    while (gamewindow.isOpen())
    {



        while (gamewindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed){
                gamewindow.close();
            }
            if(event.type == Event::MouseButtonPressed){

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    Vector2f clickerLocation = gamewindow.mapPixelToCoords(sf::Mouse::getPosition(gamewindow));
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 25; j++) {
                            if (all_tiles[i][j].tile.getGlobalBounds().contains(clickerLocation) &&
                                !all_tiles[i][j].flagCheck() && mine_board.updateBoard()) {
                                all_tiles[i][j].TileReveal();
                                if (all_tiles[i][j].mineSetCheck()) {
                                    mine_board.endMinesweeper();
                                } else {
                                    all_tiles[i][j].revealPosofMine();
                                }

                            }
                        }
                    }
                    if (sprite_buttons[1].getButtonSprite().getGlobalBounds().contains(clickerLocation)) {

                        mine_board.loadtimeRun(true);
                        clock.restart();
                        mine_board.boardCreate(all_mines,flaggedmines,all_tiles,numtot_mines);

                         }
                    else if (sprite_buttons[3].getButtonSprite().getGlobalBounds().contains(clickerLocation) &&
                             !mine_board.getDebugMode()) {
                        mine_board.loadDebugger(true);

                    } else if (sprite_buttons[3].getButtonSprite().getGlobalBounds().contains(clickerLocation) &&
                               mine_board.getDebugMode()) {
                        mine_board.loadDebugger(false);
                    } else if (sprite_buttons[4].getButtonSprite().getGlobalBounds().contains(clickerLocation) && !mine_board.getPause())
                    {
                        cout << mine_board.getPause() <<endl;
                        cout <<" game paused" <<endl;
                       mine_board.loadPause(true);
                        cout << mine_board.getPause() <<endl;

                    }
                    else if (sprite_buttons[4].getButtonSprite().getGlobalBounds().contains(clickerLocation) && mine_board.getPause()){
                        cout << " game unpaused" <<endl;
                        mine_board.loadPause(false);
                    }


                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Vector2f mousePos = gamewindow.mapPixelToCoords(sf::Mouse::getPosition(gamewindow));
                    bool can = true;
                    while (can == true) {


                        for (int i = 0; i < 16; i++) {
                            for (int j = 0; j < 25; j++) {
                                if (all_tiles[i][j].tile.getGlobalBounds().contains(mousePos) && !all_tiles[i][j].flagCheck() && !all_tiles[i][j].RevealTile() && mine_board.updateBoard()) {
                                    mine_board.placeFlag(flaggedmines, all_tiles[i][j]);

                                }
                                else if (all_tiles[i][j].tile.getGlobalBounds().contains(mousePos) && !all_tiles[i][j].RevealTile() && all_tiles[i][j].flagCheck() && mine_board.updateBoard()) {
                                    mine_board.removeFlag( all_tiles[i][j],flaggedmines);
                                }
                            }
                        }
                        can = false;
                    }
                }
                break;

            }


        }
        timeNow=clock.getElapsedTime().asSeconds();
        minutes= timeNow/60;
        seconds =timeNow %60;

        minin10place = (minutes/10) %10;
        minin1place =(minutes%10);
        secondin10place=(seconds/10)%10;
        secondin1place=(seconds%10);
        gamewindow.clear();

        mine_board.setBoardCreate(flaggedmines,gamewindow,numtot_mines,minecount_tot,sprite_buttons,mine_board.updateBoard(),totmine_vect,mine_board.getDebugMode(),all_tiles,all_mines,secondin1place,secondin10place,minin1place,minin10place);
        gamewindow.display();

    }
    return 0;
    TxtManager ::Clear();

}
