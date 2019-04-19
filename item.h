#ifndef _ITEM_H_
#define _ITEM_H_

#include <cmath>
#include "drawable.h"
#include "renderContext.h"
#include "gameData.h"
#include <vector>

class Item : public Drawable {

public:
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  Item(std::string, int, int);
  Item(const Item&) = delete;
  Item& operator=(const Item&) = delete;
  ~Item();
private:
  Image * sprite;
  int cur_row, cur_col;
  int ellapsed_time;
};

#endif
