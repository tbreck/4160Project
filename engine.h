#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "BoardManager.h"
#include "BackgroundTile.h"
#include "HUDDisplay.h"

class Engine {
public:
  Engine (int size);
  ~Engine ();
  void play();
  void switchSprite();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  BoardManager board;

  bool HUD_ON;

private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  HUDDisplay *HUD;
  //std::vector<Drawable*> backgroundTiles;
  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
  void Active_HUD();
  void No_HUD();
};

#endif
