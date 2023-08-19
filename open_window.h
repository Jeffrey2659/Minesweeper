
#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace  sf;
using namespace  std;
#define BACKSPACE 8
#define  TAB 9
#define ESCAPE 27

class Textbox{

public:
Textbox(){ }

Textbox(int size,Color color,bool selected){
    textbox.setCharacterSize(size);
    textbox.setFillColor(color);
    isSelect=selected;
    if(selected){
        textbox.setString("|");
    }
    else{
        textbox.setString("");
    }
}
 void setFont(Font & font){
    textbox.setFont(font);
}
void setPosition(Vector2f pos){
    FloatRect  bounds(textbox.getLocalBounds());
    textbox.setOrigin(bounds.left + bounds.width/2.0f,
                      bounds.top  +bounds.height/2.0f);
    textbox.setPosition(pos);
}
void setLimit(bool Tof,int max){
    charLimit = Tof;
    limit =max-1;
}
void setSelected(bool selVal){
    isSelect =selVal;
    if(!selVal){
        string t =text.str();
        string newLet= "";
        for(int i =0; i < t.length();i++){
            newLet +=t[i];
        }
        textbox.setString(newLet);
    }
}
    string getText(){
        return  text.str();
}
void drawtoScreen(RenderWindow &window){
    window.draw(textbox);
}
// this is where the input get processed so create a seperate function to turn the first letter into uppercase
void typeInput(Event input){
    if(isSelect){
        int charinput= input.text.unicode;
        if((charinput <= 122 && charinput >=97) || (charinput >= 65 && charinput <=90 )|| charinput == 8){
            if(charLimit){
                if(text.str().length() <= limit){
                    inputLog(charinput);

                }
                else if(text.str().length() > limit && Keyboard ::isKeyPressed(sf::Keyboard::BackSpace)){
                deleteletter();
                }
            }
            else{
                inputLog(charinput);
            }
        }
    }
}
    private:
    Text textbox;
    ostringstream text;
    bool  isSelect= false;
    bool charLimit=false;
    int limit;

    void inputLog(int charinput){
     if(charinput != BACKSPACE && charinput !=ESCAPE &&charinput != TAB ){

         text << static_cast<char>(charinput);

     }
     else if(charinput == BACKSPACE){
         if(text.str().length() >0){
            deleteletter();
         }
     }
        uppercase();
     //textbox.setString(text.str()+ "|");


    }
    void  deleteletter(){
        string t =text.str();
        string newLet= "";
        for(int i =0; i < t.length()-1;i++){
            newLet +=t[i];
        }
        text.str(""); // clearing the string object
        text << newLet;
        textbox.setString(text.str());
    }


    void uppercase(){
        string letters=text.str();
        string newName= "";

            if (islower(letters[0])) {
                newName += ::toupper(letters[0]);
            }
            if (isupper(letters[0])) {

               newName+= letters[0];

            }
            for (int i = 1; i < letters.length(); i++) {

            newName += ::tolower(letters[i]);
        }


        text.str("");
        text <<newName;
        textbox.setString(text.str() + "|");
    }
    };

/*if(!isupper(letters[0])){

            for(int i=1; i < letters.length();i++)
                {
            newName+= ::tolower(letters[i]);
                }
            }
        else if(!isupper(letters[0])){
            newName+= ::toupper(letters[0]);
        }*/