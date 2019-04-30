#include "Projectile.h"

void Projectile::moveDirection(int direction, int tiles) {
  switch (direction) {
    case 0: setX(getX() - tiles); break; // Move Left
    case 1: setX(getX() + tiles); break; // Move Right
    case 2: setY(getY() - tiles); break; // Move Up
    case 3: setY(getY() + tiles); break; // Move Down
  }
  cur_row = getX() / 100;
  cur_col = getY() / 100;
}
void Projectile::draw() const {
  sprite->draw(getX(), getY(), getScale());
}
void Projectile::update(Uint32 ticks) {
  ellapsed_time += ticks;
}
int Projectile::getScaledWidth()  const {
  return getScale() * sprite->getWidth();
}
int Projectile::getScaledHeight()  const {
  return getScale() * sprite->getHeight();
}
int Projectile::getCurRow() const {
  return cur_row;
}
int Projectile::getCurCol() const {
  return cur_col;
}
const Image* Projectile::getImage() const {
  return sprite;
}
const SDL_Surface* Projectile::getSurface() const {
  return sprite->getSurface();
}
Projectile::Projectile(std::string tag, int row, int col) :
  Drawable(tag, Vector2f(row * 100, col * 100), Vector2f(0, 0), 1.0),
  sprite (ImageFactory::getInstance().getImage(tag)),
  cur_row(row),
  cur_col(col),
  ellapsed_time(0) {
    if (tag == "Left_Arrow") ID = 0;
    else if (tag == "Right_Arrow") ID = 1;
    else if (tag == "Up_Arrow") ID = 2;
    else if (tag == "Down_Arrow") ID = 3;
  }

Projectile::~Projectile() {
  delete sprite;
}

int Projectile::getID() {
  return ID;
}
