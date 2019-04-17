#include "BoardManager.h"
#include <sstream>
/*==============================================================================
==============================================================================*/
BoardManager::BoardManager(int s) {
  this->size = s;
  tiles.resize(s);
  /* Resizing the table to fit to the argument given. */
  for (auto &tile : tiles) tile.resize(s);
  //for (auto &val : map) val.resize(s);

  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      std::stringstream ss;
      ss << i << j;
      map[i][j] = Gamedata::getInstance().getXmlInt("map/t" + ss.str());
    }
  }
  /* Will ONLY work with perfect square. */
  for ( int row = 0; row < s; row++ ) {
    for ( int col = 0; col < s; col++ ) {
      std::stringstream ss;
      ss << "Tile" << map[row][col];
      tiles[row][col] = new BackgroundTile(ss.str(), (row * 100), (col * 100));
    }
  }

  this->human = new Player("human", 0, 0);
  this->ai = new Player("human", 3, 3);
}
/*==============================================================================
==============================================================================*/
void BoardManager::drawTiles() const {
  for (unsigned int i = 0; i < this->size; i++) {
    for (unsigned int j = 0; j < this->size; j++) {
      tiles[i][j]->draw();
    }
  }
  human->draw();
  ai->draw();
}
/*==============================================================================
==============================================================================*/
void BoardManager::update(Uint32 ticks) {
  human->update(ticks);
  ai->update(ticks);
}
/*==============================================================================
==============================================================================*/
BoardManager::~BoardManager() {
  for (auto& row : tiles)
    for (auto& tile : row) delete tile;
  // delete human;
  // delete ai;
}
/*==============================================================================
==============================================================================*/
Drawable* BoardManager::getTile() {
  return tiles[0][0];
}
/*==============================================================================
==============================================================================*/
int BoardManager::getPlayerX(int player) {
  if (player == 0)
    return human->getX();
  else return ai->getX();
}
/*==============================================================================
==============================================================================*/
int BoardManager::getPlayerY(int player) {
  if (player == 0)
    return human->getY();
  else return ai->getY();
}
/*==============================================================================
==============================================================================*/
void BoardManager::movePlayer(int player, int dir, int tiles) {
  if (player == 0) {
    // Move Left
    if (dir == 0 && (human->getX()-tiles) >= 0 && ((ai->getX() != human->getX() - tiles) || (ai->getY() != human->getY()))){
      human->moveDirection(dir, tiles);
      // std::cout << "move!" << std::endl;
    }
    // Move Right
    else if (dir == 1 && (human->getX()-tiles ) < (size-2) * tiles && ((ai->getX() != human->getX() + tiles) || (ai->getY() != human->getY()))){
      human->moveDirection(dir, tiles);
      // std::cout << "move!" << std::endl;
    }
    //Move Up
    else if (dir == 2 && (human->getY()-tiles) >= 0 && ((ai->getY() != human->getY() - tiles) || (ai->getX() != human->getX()))){
      human->moveDirection(dir, tiles);
      // std::cout << "move!" << std::endl;
    }
    //Move Down
    else if (dir == 3 && (human->getY()-tiles) < (size-2) * tiles && ((ai->getY() != human->getY() + tiles) || (ai->getX() != human->getX()))){
      human->moveDirection(dir, tiles);
      // std::cout << "move!" << std::endl;
    }

  } else {
    if (dir == 0 && (ai->getX()-tiles) >= 0
                 && ((human->getX() != ai->getX() - tiles)
                 || (human->getY() != ai->getY())))
      ai->moveDirection(dir, tiles);
    else if (dir == 1 && (ai->getX()-tiles ) < (size-2) * tiles
                      && ((human->getX() != ai->getX() + tiles)
                      || (human->getY() != ai->getY())))
      ai->moveDirection(dir, tiles);
    else if (dir == 2 && (ai->getY()-tiles) >= 0
                      && ((human->getY() != ai->getY() - tiles)
                      || (human->getX() != ai->getX())))
      ai->moveDirection(dir, tiles);
    else if (dir == 3 && (ai->getY()-tiles) < (size-2) * tiles
                      && ((human->getY() != ai->getY() + tiles)
                      || (human->getX() != ai->getX())))
      ai->moveDirection(dir, tiles);
    //AI movement
  }
}
