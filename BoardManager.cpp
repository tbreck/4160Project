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
      tiles[row][col] = new BackgroundTile(ss.str(), (row * 100), (col * 100), map[row][col]);
    }
  }

  for ( int row = 0; row < s; row++ ) {
    for ( int col = 0; col < s; col++ ) {
      /* If item placeholder detected. */
      if (map[row][col] == 4) {
        items[row][col] = new Item("Crate", row * 100, col * 100);
      }
    }
  }

  this->human = new Player("human", 0, 0);
  this->ai = new Player("human", 8, 9);
}
/*==============================================================================
==============================================================================*/
void BoardManager::drawTiles() const {
  for (unsigned int i = 0; i < this->size; i++) {
    for (unsigned int j = 0; j < this->size; j++) {
      tiles[i][j]->draw();
      if (map[i][j] == 4) {
        items[i][j]->draw();
      }
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
void BoardManager::movePlayer(int player, int dir, int t) {

  /* Tiles 3 and 4 are walkable. */

  /* HUMAN */
  if (player == 0) {
    // Move Left
    if (dir == 0 && (human->getX()-t) >= 0 && ((ai->getX() != human->getX() - t) || (ai->getY() != human->getY()))
        && tiles[(human->getX() - 1) / 100][human->getY() / 100]->isWalkable){
      human->moveDirection(dir, t);
      // std::cout << "move!" << std::endl;
    }
    // Move Right
    else if (dir == 1 && (human->getX()-t ) < (size-2) * t && ((ai->getX() != human->getX() + t) || (ai->getY() != human->getY()))
             && tiles[((human->getX() + 1) / 100) + 1][human->getY() / 100]->isWalkable){
      human->moveDirection(dir, t);
      // std::cout << "move!" << std::endl;
    }
    //Move Up
    else if (dir == 2 && (human->getY()-t) >= 0 && ((ai->getY() != human->getY() - t) || (ai->getX() != human->getX()))
             && tiles[human->getX() / 100][(human->getY() - 1) / 100]->isWalkable){
      human->moveDirection(dir, t);
      // std::cout << "move!" << std::endl;
    }
    //Move Down
    else if (dir == 3 && (human->getY()-t) < (size-2) * t && ((ai->getY() != human->getY() + t) || (ai->getX() != human->getX()))
             && tiles[human->getX() / 100][((human->getY() + 1) / 100) + 1]->isWalkable){
      human->moveDirection(dir, t);
      // std::cout << "move!" << std::endl;
    }

    /* AI */
  } else {
    if (dir == 0 && (ai->getX()-t) >= 0
                 && ((human->getX() != ai->getX() - t)
                 || (human->getY() != ai->getY()))
                 && tiles[(ai->getX() - 1) / 100][ai->getY() / 100]->isWalkable)
      ai->moveDirection(dir, t);
    else if (dir == 1 && (ai->getX()-t ) < (size-2) * t
                      && ((human->getX() != ai->getX() + t)
                      || (human->getY() != ai->getY()))
                      && tiles[((ai->getX() + 1) / 100) + 1][ai->getY() / 100]->isWalkable)
      ai->moveDirection(dir, t);
    else if (dir == 2 && (ai->getY()-t) >= 0
                      && ((human->getY() != ai->getY() - t)
                      || (human->getX() != ai->getX()))
                      && tiles[ai->getX() / 100][(ai->getY() - 1) / 100]->isWalkable)
      ai->moveDirection(dir, t);
    else if (dir == 3 && (ai->getY()-t) < (size-2) * t
                      && ((human->getY() != ai->getY() + t)
                      || (human->getX() != ai->getX()))
                      && tiles[ai->getX() / 100][((ai->getY() + 1) / 100) + 1]->isWalkable)
      ai->moveDirection(dir, t);
    //AI movement
  }
}
