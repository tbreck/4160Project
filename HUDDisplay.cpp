#include "HUDDisplay.h"
#include "renderContext.h"
#include "gameData.h"

void HUDDisplay::draw() const {
  HUD->draw(getX(), getY(), getScale());
}
void HUDDisplay::update(Uint32 ticks) {
  life_span += ticks;
}
int HUDDisplay::getScaledWidth()  const {
  return getScale() * HUD->getWidth();
}
int HUDDisplay::getScaledHeight()  const {
  return getScale() * HUD->getHeight();
}
const Image* HUDDisplay::getImage() const {
  return HUD;
}
const SDL_Surface* HUDDisplay::getSurface() const {
  return HUD->getSurface();
}
HUDDisplay::HUDDisplay(const std::string& HUD_image) :
  Drawable(HUD_image, Vector2f(0, 0), Vector2f(0, 0), 1.0),
  humanHasBow(false),
  AIHasBow(false),
  HUD( ImageFactory::getInstance().getImage(HUD_image) ),
  life_span(0) {
    humanBow = new Item("Bow", 289, 15, 1);
    AIBow = new Item("Bow", 672, 15, 1);
  }

HUDDisplay::~HUDDisplay() {
  delete HUD;
}
