#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include <cmath>
#include "drawable.h"
#include "renderContext.h"
#include "gameData.h"
#include <vector>

class Projectile : public Drawable {
public:
  void moveDirection(int, int);
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;
  int getCurRow() const;
  int getCurCol() const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  int getID();
  Projectile(std::string, int, int);
  Projectile(const Projectile&) = delete;
  Projectile& operator=(const Projectile&) = delete;
  ~Projectile();
private:
  Image * sprite;
  int ID;
  int ellapsed_time;
  int cur_row, cur_col;
};

#endif
