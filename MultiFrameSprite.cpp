#include "MultiFrameSprite.h"
#include "renderContext.h"
#include "gameData.h"

MultiFrameSprite::~MultiFrameSprite() {
  for (auto& image: images) {
    delete image;
  }
}

const Image* MultiFrameSprite::getImage() const {
  return images[currentFrame];
}

int MultiFrameSprite::getScaledWidth()  const {
  return getScale() * images[currentFrame]->getWidth();
}

int MultiFrameSprite::getScaledHeight()  const {
  return getScale() * images[currentFrame]->getHeight();
}
const SDL_Surface* MultiFrameSprite::getSurface() const {
  return images[currentFrame]->getSurface();
}

MultiFrameSprite::MultiFrameSprite(const std::string& name) :
  Drawable(name, Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                          Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
                 Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                          Gamedata::getInstance().getXmlInt(name+"/speedY")),
                 Gamedata::getInstance().getXmlFloat(name+"/scale")),
  images( ImageFactory::getInstance().getImages(name) ),
  deltaTimeFrame(0),
  currentFrame(0),
  leftFrames( Gamedata::getInstance().getXmlInt(name+"/lf") ),
  rightFrames(Gamedata::getInstance().getXmlInt(name+"/rf") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/fi") ),
  worldWidth( Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")) {

  /* Jank factor level 9001 */
  position[0] = position[0] + rand() % Gamedata::getInstance().getXmlInt("world/width");
  position[1] = position[1] + rand() % Gamedata::getInstance().getXmlInt("world/height");
}

void MultiFrameSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void MultiFrameSprite::advanceFrame(uint32_t ticks) {
  deltaTimeFrame += ticks;
  if (deltaTimeFrame > frameInterval) {
    if (getVelocityX() > 0 ) {
      currentFrame = (currentFrame+1) % leftFrames;
    } else {
      currentFrame = leftFrames + (currentFrame+1) % rightFrames;
    }
    deltaTimeFrame = 0;
  }
}

void MultiFrameSprite::update(uint32_t ticks) {
  advanceFrame(ticks);

  Vector2f add = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + add);

  /* Correct x*/
  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  else if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }
  /* Correct y */
  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  else if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }
}
