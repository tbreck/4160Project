#ifndef _HUDDISPLAY_H_
#define _HUDDISPLAY_H_

#include <cmath>
#include "drawable.h"
#include <vector>

class HUDDisplay : public Drawable {

public:
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  HUDDisplay(const std::string&);
  HUDDisplay(const HUDDisplay&) = delete;
  HUDDisplay& operator=(const HUDDisplay&) = delete;
  ~HUDDisplay();
private:
  Image *HUD;
  int life_span;
};

#endif
