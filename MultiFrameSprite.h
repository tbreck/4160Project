#ifndef _MULTIFRAMESPRITE_H
#define _MULTIFRAMESPRITE_H

#include <cmath>
#include "drawable.h"
#include <vector>

class MultiFrameSprite : public Drawable {
public:
  /* Few helper functions, as well as defined virtual functions. */
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  void advanceFrame(Uint32 ticks);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;


  /* Rule of 3 because of Image* */
  MultiFrameSprite(const std::string&);
  MultiFrameSprite(const MultiFrameSprite&) = delete;
  MultiFrameSprite& operator=(const MultiFrameSprite&) = delete;
  ~MultiFrameSprite();

private:
  std::vector<Image *> images;

  /* All used to determine current frame to use, and when to use. */
  /* I'm a fan of naming variables like this: var_one
     But to keep with the style of this program, I'm doing camel case.
     What I'm saying is that the MIDI visualizer will be stylistically
     incompatible with this. Sorry */

  float deltaTimeFrame;
  unsigned int currentFrame;
  unsigned int leftFrames;  //Determine when we need to advance left.
  unsigned int rightFrames; //Determine when we need to advance right.
  unsigned int frameInterval;

  /* Used for convinience of accessing XML. */
  int worldWidth;
  int worldHeight;

};
#endif
