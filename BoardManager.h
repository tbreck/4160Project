#ifndef _BOARD_MANAGER_H
#define _BOARD_MANAGER_H

#include <cmath>
#include "drawable.h"
#include "gameData.h"
#include "BackgroundTile.h"
#include "Player.h"
#include "sprite.h"
#include "item.h"
#include "Projectile.h"
#include "imageFactory.h"
#include <vector>

class BoardManager {

public:
  BoardManager(int s);
  void drawTiles() const;
  void update(Uint32 ticks);
  ~BoardManager();
  Drawable* getTile();
  int movePlayer(int, int, int);
  int getPlayerX(int);
  int getPlayerY(int);
  bool playerHasBow(int) const;
  void createProjectile(int row, int col, int dir);
  int getObjects() const;
  void godMode();
  void updateStatus();
  bool humanHasBow;
  bool AIHasBow;
  Player *human;
  Player *ai;
  bool endgame;
private:
  std::vector<std::vector<BackgroundTile*>> tiles;
  std::vector<Projectile*> projectiles;
  //std::vector<std::vector<Item*>> items;
  Item *items[10][10];
  //std::vector<Player> players;
  int map[10][10];
  unsigned int size;
};

#endif
