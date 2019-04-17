#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <cmath>
#include "drawable.h"
#include "renderContext.h"
#include "gameData.h"
#include <vector>

class Player : public Drawable {
public:
  void moveDirection(int, int);
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getScaledWidth()  const;
  int getScaledHeight()  const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  Player(std::string, int, int);
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  ~Player();

private:

  std::vector<Image*> sprites;
  int cur_row, cur_col;
  int current_frame;
  int anim_frames;
  int damage_frame;
  //std::vector<Item*> held_items;
  int health;
  int movements_left;
  int attacks_left;
  int frame_interval;
  int ellapsed_time;
  int total_tiles;



};


#endif
