#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "sound.h"
#include "multisprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "MultiFrameSprite.h"
#include "BackgroundTile.h"
#include "BoardManager.h"

Engine::~Engine() {
  sprites.clear();
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine(int size) :
board(size),
HUD_ON(false),
rc( RenderContext::getInstance() ),
io( IoMod::getInstance() ),
clock( Clock::getInstance() ),
music( new SDLSound() ),
renderer( rc->getRenderer() ),
viewport( Viewport::getInstance() ),
sprites(),
HUD(new HUDDisplay("HUD")),
currentSprite(0),
makeVideo( false )
{
  Viewport::getInstance().setObjectToTrack(board.getTile());
  std::cout << "Construction of Engine complete" << std::endl;
}

void Engine::draw() {
  SDL_Color Name_color = {255, 100, 0, 255};
  board.drawTiles();
  io.writeText("Colt Gainey & Tanner Breckenridge", 20, 900, Name_color);

  for (unsigned int i = 0; i < sprites.size(); i++) {
    sprites[i]->draw();
  }
  if (board.endgame) {
    (*music)[2];
    io.writeText("Press R to Restart the game", 365, 500);
    clock.pause();
    /* This is a very hacky way to create a restart */
    board.updateStatus();
  }
  if (HUD_ON){
    HUD->setX(0);
    HUD->draw();
    std::stringstream fps;
    fps << clock.getFps();
    io.writeText(fps.str(), 270, 125, Name_color);
    int objs = board.getObjects();
    std::stringstream obj_strm;
    obj_strm << "OBJECTS: " << objs;
    io.writeText(obj_strm.str(), 800, 25, Name_color);
    if (board.humanHasBow) {
      HUD->humanBow->draw();
    }
    if (board.AIHasBow) {
      HUD->AIBow->draw();
    }
  } else if (!HUD_ON){ // .... yes we know this is hacky
    HUD->setX(-1000);
    HUD->draw();
  }


  //viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {

  board.update(ticks);
  for (unsigned int i = 0; i < sprites.size(); i++) {
    sprites[i]->update(ticks);
  }
  if (HUD_ON) HUD->update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}


void Engine::Active_HUD() {
  if (!HUD_ON) {
    HUD_ON = true;
  }
}
void Engine::No_HUD() {
  if (HUD_ON) {
    HUD_ON = false;
  }
}

void Engine::play() {
  srand(time(NULL));
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  int cur_player = 0;

  while ( !done ) {
    if ((cur_player % 2) == 1) {
      int player_x = board.getPlayerX(0);
      int ai_x = board.getPlayerX(1);
      int player_y = board.getPlayerY(0);
      int ai_y = board.getPlayerY(1);
      /* Flip a coin to see if we will go up or down. */
      if (rand() % 2 == 0) {
        /* If the player is to the right, go right. */
        if (board.AIHasBow) {
          board.createProjectile(board.ai->getCurRow(), board.ai->getCurCol(), (rand() % 3));
        }
        if (player_x > ai_x) board.movePlayer(1, 1, 100);
        /* Otherwise, go left. */
        else board.movePlayer(1, 0, 100);
      } else {
        /* If the player is below us, go down. */
        if (player_y > ai_y) board.movePlayer(1, 3, 100);
        /* Otherwise, go up. */
        else board.movePlayer(1, 2, 100);
      }


    }
    //This whole key register is very hacky, only way that we were able to get the F1 to work properly
    else {
      bool action_registered = false;
      // The next loop polls for events, guarding against key bounce:
      while (!action_registered ) {
        /* Update the frames while we wait for the player to act. */
        ticks = clock.getElapsedTicks();
        if ( ticks > 0 ) {
          clock.incrFrame();
          draw();
          update(ticks);
          if ( makeVideo ) {
            frameGen.makeFrame();
          }
        }
        while ( SDL_PollEvent(&event) ) {
          keystate = SDL_GetKeyboardState(NULL);
          if (event.type ==  SDL_QUIT) { done = true; action_registered = true; break; }
          if(event.type == SDL_KEYDOWN) {
            if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
              done = true;
              action_registered = true;
              break;
            }

            if ( keystate[SDL_SCANCODE_P] ) {
              if ( clock.isPaused() ) clock.unpause();
              else clock.pause();
              (*music)[0];
            }
            /* MUSIC PAUSED =================================================== */
            if ( keystate[SDL_SCANCODE_SPACE] ) {
              music->toggleMusic();
            }
            /*F1 has key bounce pretty bad ==================================== */
            else if (keystate[SDL_SCANCODE_F1]) {
              if (!HUD_ON) Active_HUD();
              else No_HUD();
              (*music)[0];
            }
            /* A ============================================================== */
            else if (keystate[SDL_SCANCODE_A]) {
              action_registered = true;
              (*music)[1];
              int ret_val = board.movePlayer(0, 0, 100);
              if (ret_val != 0) {
                (*music)[2];
              }
            }
            /* D ============================================================== */
            else if (keystate[SDL_SCANCODE_D]) {
              action_registered = true;
              (*music)[1];
              int ret_val = board.movePlayer(0, 1, 100);
              if (ret_val != 0) {
                (*music)[2];
              }
            }
            /* W ============================================================== */
            else if (keystate[SDL_SCANCODE_W]) {
              action_registered = true;
              (*music)[1];
              int ret_val = board.movePlayer(0, 2, 100);
              if (ret_val != 0) {
                (*music)[2];
              }
            }
            /* S ============================================================== */
            else if (keystate[SDL_SCANCODE_S]) {
              action_registered = true;
              (*music)[1];
              int ret_val = board.movePlayer(0, 3, 100);
              if (ret_val != 0) {
                (*music)[2];
              }
            }
            /* R ============================================================== */
            else if (keystate[SDL_SCANCODE_R]) {
              clock.unpause();
              board.human = new Player("human", 0, 0);
              board.humanHasBow = false;
              board.ai = new Player("AI", 8, 9);
              board.AIHasBow = false;

            }
            /* G ============================================================== */
            else if (keystate[SDL_SCANCODE_G]) {
              board.godMode();
              std::cout << "God Mode Toggled! You cheater...." << std::endl;
            }
            else if (keystate[SDL_SCANCODE_LEFT]) {
              if (board.humanHasBow) {
                board.createProjectile(board.human->getCurRow(), board.human->getCurCol(), 0);
              }
            }
            else if (keystate[SDL_SCANCODE_RIGHT]) {
              if (board.humanHasBow) {
                board.createProjectile(board.human->getCurRow(), board.human->getCurCol(), 1);
              }
            }
            else if (keystate[SDL_SCANCODE_UP]) {
              if (board.humanHasBow) {
                board.createProjectile(board.human->getCurRow(), board.human->getCurCol(), 2);
              }
            }
            else if (keystate[SDL_SCANCODE_DOWN]) {
              if (board.humanHasBow) {
                board.createProjectile(board.human->getCurRow(), board.human->getCurCol(), 3);
              }
            }
          }
        }
      }
    }
    // In this section of the event loop we allow key bounce:
    cur_player++;
  }
}


// if ( sprites.size() == 0 && explosionsFinished ) {
//     io.writeText("Press R to Restart the game", 250, 200);
//     clock.pause();
//   }
