
#include "ButtonSetup.h"
#include "boardsetup.h"
using namespace std;
using namespace sf;
ButtonSetup::ButtonSetup(const char* name) {
    setButtonSprite(name);
}
void ButtonSetup::setButtonSprite(const char* name) {
    this->image.setTexture(TxtManager::getTextureInfo(name));
}
sf::Sprite& ButtonSetup::getButtonSprite() {
    return this->image;
}
void ButtonSetup::setButtonPosition(float width, float height) {

    this->getButtonSprite().setPosition(width, height);
}