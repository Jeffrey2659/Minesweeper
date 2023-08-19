
#include "flagcount.h"
flagcount::flagcount(int num) {
    setSprite("digits");
    getSprite().setTextureRect(sf::IntRect((num * 21), 0, 21, 32));
}
