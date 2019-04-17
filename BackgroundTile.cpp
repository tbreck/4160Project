#include "BackgroundTile.h"
#include "renderContext.h"
#include "gameData.h"

void BackgroundTile::draw() const {
  tile->draw(getX(), getY(), getScale());
}
/*==============================================================================
==============================================================================*/
void BackgroundTile::update(Uint32 ticks) { life_span += ticks; }
/*==============================================================================
==============================================================================*/
int BackgroundTile::getScaledWidth()  const {
  return getScale() * tile->getWidth();
}
/*==============================================================================
==============================================================================*/
int BackgroundTile::getScaledHeight()  const {
  return getScale() * tile->getHeight();
}
/*==============================================================================
==============================================================================*/
const Image* BackgroundTile::getImage() const {
  return tile;
}
/*==============================================================================
==============================================================================*/
const SDL_Surface* BackgroundTile::getSurface() const {
  return tile->getSurface();
}
/*==============================================================================
==============================================================================*/
BackgroundTile::BackgroundTile(const std::string& tile_id,
                               int x, int y) :
  Drawable(tile_id, Vector2f(x, y), Vector2f(0, 0), 1.0),
  tile( ImageFactory::getInstance().getImage(tile_id) ),
  item_on_tile(false),
  player_on_tile(false),
  x_offset(x),
  y_offset(y),
  life_span(0) {}
/*==============================================================================
==============================================================================*/
BackgroundTile::~BackgroundTile() {
  // delete tile;
}
