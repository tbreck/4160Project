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
  int getCurRow() const;
  int getCurCol() const;
  virtual const Image* getImage() const;
  virtual const SDL_Surface* getSurface() const;
  Player(std::string, int, int);
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  ~Player();
  int cur_row, cur_col;
  bool bow;
  int current_frame;

private:

  std::vector<Image*> sprites;
  int anim_frames;
  int damage_frame;
  int frame_interval;
  int ellapsed_time;
  int total_tiles;



};


#endif
