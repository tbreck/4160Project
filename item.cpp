#include "item.h"

void Item::draw() const {
  sprite->draw(getX(), getY(), getScale());
}
void Item::update(Uint32 ticks) {
  ellapsed_time += ticks;
}
int Item::getScaledWidth()  const {
  return getScale() * sprite->getWidth();
}
int Item::getScaledHeight()  const {
  return getScale() * sprite->getHeight();
}
const Image* Item::getImage() const {
  return sprite;
}
const SDL_Surface* Item::getSurface() const {
  return sprite->getSurface();
}
Item::Item(std::string tag, int row, int col, int s) :
  Drawable(tag, Vector2f(row * s, col * s), Vector2f(0, 0), 1.0),
  sprite (ImageFactory::getInstance().getImage(tag)),
  cur_row(row),
  cur_col(col),
  ellapsed_time(0) {}

/* Responsible for freeing sprite. */
Item::~Item() {}
