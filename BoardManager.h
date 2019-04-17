#ifndef _BOARD_MANAGER_H
#define _BOARD_MANAGER_H

#include <cmath>
#include "drawable.h"
#include "gameData.h"
#include "BackgroundTile.h"
#include "Player.h"
#include <vector>

class BoardManager {

public:
  BoardManager(int s);
  void drawTiles() const;
  void update(Uint32 ticks);
  ~BoardManager();
  Drawable* getTile();
  void movePlayer(int, int, int);
  int getPlayerX(int);
  int getPlayerY(int);

private:
  std::vector<std::vector<BackgroundTile*>> tiles;
    //std::vector<std::vector<Item*>> items;
  //std::vector<Player> players;
  Player *human;
  Player *ai;
  int map[10][10];
  unsigned int size;
};

#endif
