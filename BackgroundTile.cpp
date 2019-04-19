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
                               int x, int y, int _ID) :
  Drawable(tile_id, Vector2f(x, y), Vector2f(0, 0), 1.0),
  tile( ImageFactory::getInstance().getImage(tile_id) ),
  player_on_tile(false),
  x_offset(x),
  y_offset(y),
  life_span(0),
  ID(_ID) {
    /* Set item states and walkable state based on the ID based in. */
    switch (ID) {
      case 1: isWalkable = false; item_on_tile = false; break;
      case 2: isWalkable = false; item_on_tile = false; break;
      case 3: isWalkable = true;  item_on_tile = false; break;
      case 4: isWalkable = true;  item_on_tile = true;  break;
      case 5: isWalkable = false; item_on_tile = false; break;
      case 6: isWalkable = false; item_on_tile = false; break;
      case 7: isWalkable = false; item_on_tile = false; break;
      case 8: isWalkable = false; item_on_tile = false; break;
    }
  }
/*==============================================================================
==============================================================================*/
BackgroundTile::~BackgroundTile() {
  // delete tile;
}
