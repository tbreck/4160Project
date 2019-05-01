#include "BoardManager.h"
#include <sstream>
/*==============================================================================
==============================================================================*/
BoardManager::BoardManager(int s){
  this->size = s;
  tiles.resize(s);
  /* Resizing the table to fit to the argument given. */
  for (auto &tile : tiles) tile.resize(s);

  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++ ) {
      items[i][j] = NULL;
    }
  }

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
        std::stringstream ss;
        ss << "Crate";
        items[row][col] = new Item(ss.str(), row, col, 100);
      }
    }
  }
  humanHasBow = false;
  AIHasBow = false;

  this->human = new Player("human", 0, 0);
  this->ai = new Player("AI", 8, 9);
}
/*==============================================================================
==============================================================================*/
bool BoardManager::playerHasBow(int p) const{
  if (p == 0) {
    return human->bow;
  } else {
    return ai->bow;
  }
}
/*==============================================================================
==============================================================================*/
void BoardManager::createProjectile(int row, int col, int dir) {
  switch(dir) {
    case 0:
      if (map[row-1][col] == 3 || map[row-1][col] == 4)
        projectiles.push_back(new Projectile("Left_Arrow", row-1, col));
      break;
    case 1:
      if (map[row+1][col] == 3 || map[row+1][col] == 4)
        projectiles.push_back(new Projectile("Right_Arrow", row+1, col));
      break;
    case 2:
      if (map[row][col-1] == 3 || map[row][col-1] == 4)
        projectiles.push_back(new Projectile("Up_Arrow", row, col-1));
      break;
    case 3:
      if (map[row][col+1] == 3 || map[row][col+1] == 4)
        projectiles.push_back(new Projectile("Down_Arrow", row, col+1));
      break;
  }

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
  for (auto &projectile : projectiles) projectile->draw();
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

int BoardManager::getObjects() const {
  int total_objs = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (items[i][j] != NULL) total_objs++;
    }
  }
  total_objs += 2; //Player objects.
  total_objs += projectiles.size();
  return total_objs;
}
/*==============================================================================
==============================================================================*/
void BoardManager::godMode() {
  if (!human->godmode) human->godmode = true;
  else human->godmode = false;
}

/*==============================================================================
==============================================================================*/
int BoardManager::movePlayer(int player, int dir, int t) {

  /* Tiles 3 and 4 are walkable. */

  /* HUMAN */
  if (player == 0) {
    // Move Left
    if (dir == 0 && (human->getX()-t) >= 0 && ((ai->getX() != human->getX() - t) || (ai->getY() != human->getY()))
        && tiles[(human->getX() - 1) / 100][human->getY() / 100]->isWalkable){
      human->moveDirection(dir, t);
    }
    // Move Right
    else if (dir == 1 && (human->getX()-t ) < (size-2) * t && ((ai->getX() != human->getX() + t) || (ai->getY() != human->getY()))
             && tiles[((human->getX() + 1) / 100) + 1][human->getY() / 100]->isWalkable){
      human->moveDirection(dir, t);

    }
    //Move Up
    else if (dir == 2 && (human->getY()-t) >= 0 && ((ai->getY() != human->getY() - t) || (ai->getX() != human->getX()))
             && tiles[human->getX() / 100][(human->getY() - 1) / 100]->isWalkable){
      human->moveDirection(dir, t);
    }
    //Move Down
    else if (dir == 3 && (human->getY()-t) < (size-2) * t && ((ai->getY() != human->getY() + t) || (ai->getX() != human->getX()))
             && tiles[human->getX() / 100][((human->getY() + 1) / 100) + 1]->isWalkable){
      human->moveDirection(dir, t);
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
  }

  /* ITEM DETECTION ========================================================= */
  if (items[human->cur_row][human->cur_col] != NULL) {
     items[human->cur_row][human->cur_col] = new Item("Crate", -1, -1, 100);
     human->bow = true;
  }
  if (items[ai->cur_row][ai->cur_col] != NULL) {
     items[ai->cur_row][ai->cur_col] = new Item("Crate", -1, -1, 100);
     ai->bow = true;
  }
  /* Setting the Human/AI that they have a bow to work with */
  if (human->bow == true) humanHasBow = true;
  if (ai->bow == true) AIHasBow = true;

  /* PROJECTILE MAPPING & MOVEMENT ========================================= */
  bool player_hit = false;
  bool ai_hit = false;
  for (auto &projectile: projectiles) {
    projectile->moveDirection(projectile->getID(), 50);

    /* If the arrow collides with a wall, delete it. */
    if (map[projectile->getCurRow()][projectile->getCurCol()] != 3 &&
       (map[projectile->getCurRow()][projectile->getCurCol()] != 4)) {
         projectile = new Projectile("Up_Arrow", -1, -1);
    /* If the arrow collides with the human, that human dies. */
    } else if (human->getCurRow() == projectile->getCurRow() &&
               human->getCurCol() == projectile->getCurCol()){
         std::cout << "Hit on human detected!\n";
         if (!human->godmode) {
         projectile = new Projectile("Up_Arrow", -1, -1);
         player_hit = true;
       }
       else std::cout << "Ignored hit!\n";
    /* If the arrow collides with the AI, the AI dies. */
    } else if (ai->getCurRow() == projectile->getCurRow() &&
               ai->getCurCol() == projectile->getCurCol()){
         std::cout << "Hit on AI detected!\n";
         projectile = new Projectile("Up_Arrow", -1, -1);
         ai_hit = true;
    /* Otherwise, the arrow continues forward. */
    }
    // else {
    //     projectile->moveDirection(projectile->getID(), 50);
    // }
  }
  /* Necessary for some reason. Can't return in the above if chain. */
  if (ai_hit) return 2;
  else if (player_hit) return 1;
  return 0;
}
