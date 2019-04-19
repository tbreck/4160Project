#ifndef _BACKGROUNDTILE_H_
#define _BACKGROUNDTILE_H_

#include <cmath>
#include "drawable.h"
#include <vector>

/*==============================================================================
This class serves the purpose of driving the background tiles that make up the
map.

The tiles don't change, so one frame is expected. *COULD CHANGE

The tiles are in the assets/tiles folder. They are randomly chosen from.
The amount of tiles is specified in the constructor, and must have a natural
square.
==============================================================================*/

class BackgroundTile : public Drawable {

public:
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  BackgroundTile(const std::string&, int x, int y, int _ID);
  BackgroundTile(const BackgroundTile&) = delete;
  BackgroundTile& operator=(const BackgroundTile&) = delete;
  ~BackgroundTile();
  bool isWalkable;
  int ID;

private:
  Image *tile;
  bool item_on_tile;
  bool player_on_tile;
  int x_offset, y_offset;
  int life_span; //depricated, don't delete

};


#endif
