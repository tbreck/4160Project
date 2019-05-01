#include "Player.h"

void Player::moveDirection(int direction, int tiles) {
  switch (direction) {
    case 0: setX(getX() - tiles); break; // Move Left
    case 1: setX(getX() + tiles); break; // Move Right
    case 2: setY(getY() - tiles); break; // Move Up
    case 3: setY(getY() + tiles); break; // Move Down
  }

  cur_row = getX() / 100;
  cur_col = getY() / 100;
}

void Player::draw() const {
  sprites[current_frame]->draw(getX(), getY(), getScale());
}
void Player::update(Uint32 ticks) {
  ellapsed_time += ticks;
  if (ellapsed_time > frame_interval) {
    current_frame = (current_frame + 1) % anim_frames;
    ellapsed_time = 0;
  }
}
int Player::getScaledWidth()  const {
  return getScale() * sprites[current_frame]->getWidth();
}
int Player::getCurRow() const {
  return cur_row;
}
int Player::getCurCol() const {
  return cur_col;
}
int Player::getScaledHeight()  const {
  return getScale() * sprites[current_frame]->getHeight();
}
const Image* Player::getImage() const {
  return sprites[current_frame];
}
const SDL_Surface* Player::getSurface() const {
  return sprites[current_frame]->getSurface();
}
Player::Player(std::string tag, int row, int col) :
  /*Adjust later for scale!!!!*/
  Drawable(tag, Vector2f(row * 100, col * 100), Vector2f(0, 0), 1.0),
  cur_row(row),
  cur_col(col),
  bow(false),
  godmode(false),
  current_frame(0),
  sprites (ImageFactory::getInstance().getImages(tag)),
  anim_frames(Gamedata::getInstance().getXmlInt(name+"/animFrame")),
  damage_frame(Gamedata::getInstance().getXmlInt(name+"/damageFrame")),
  frame_interval(Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  ellapsed_time(0),
  total_tiles(Gamedata::getInstance().getXmlInt("Tiles")) {}

Player::~Player() {
  for (auto& sprite: sprites) {
    delete sprite;
  }
}
