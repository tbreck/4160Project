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

void Engine::draw() const {
  SDL_Color Name_color = {255, 100, 0, 255};
  board.drawTiles();
  //io.writeText("Colt Gainey & Tanner Breckenridge", 20, 900, Name_color);

  for (unsigned int i = 0; i < sprites.size(); i++) {
    sprites[i]->draw();
  }
  if (HUD_ON){
    HUD->setX(0);
    HUD->draw();
    std::stringstream fps;
    fps << clock.getFps();
    //io.writeText(fps.str(), 0, 0, Name_color);
    if (board.humanHasBow) {
      HUD->humanBow->draw();
    }
    if (board.AIHasBow) {
      HUD->AIBow->draw();
    }
    //io.writeText("W A S D to move!", 20, 30, Name_color);
  } else if (!HUD_ON){
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
  bool music_playing = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  int cur_player = 0;
  // int HUD_toggle = 0;

  while ( !done ) {
    //if (!music_playing) music->toggleMusic();
    // bool f1_pressed = false;
    if ((cur_player % 2) == 1) {
      int player_x = board.getPlayerX(0);
      int ai_x = board.getPlayerX(1);
      int player_y = board.getPlayerY(0);
      int ai_y = board.getPlayerY(1);
      /* Flip a coin to see if we will go up or down. */
      if (rand() % 2 == 0) {
        /* If the player is to the right, go right. */
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
        if (event.type ==  SDL_QUIT) { done = true; break; }
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
          if ( keystate[SDL_SCANCODE_SPACE] ) {
            music->toggleMusic();
          }
          //F1 has key bounce pretty bad
          else if (keystate[SDL_SCANCODE_F1]) {
            if (!HUD_ON) Active_HUD();
            else No_HUD();
            (*music)[0];
          }
          else if (keystate[SDL_SCANCODE_A]) {
            action_registered = true;
            board.movePlayer(0, 0, 100);
            (*music)[1];
          }
          else if (keystate[SDL_SCANCODE_D]) {
            action_registered = true;
            board.movePlayer(0, 1, 100);
            (*music)[1];
          }
          else if (keystate[SDL_SCANCODE_W]) {
            action_registered = true;
            board.movePlayer(0, 2, 100);
            (*music)[1];
          }
          else if (keystate[SDL_SCANCODE_S]) {
            action_registered = true;
            board.movePlayer(0, 3, 100);
            (*music)[1];
          }
          /* If F is pressed: */
          else if (keystate[SDL_SCANCODE_F]) {
            if (board.humanHasBow) {
              board.shootProjectile(board.human->getCurRow(), board.human->getCurCol(), board.human->getCurRow() + 3, board.human->getCurCol());
              // while ( SDL_PollEvent(&event) ) {
              //   std::cout << "Waiting for key press..." << std::endl;
              //   keystate = SDL_GetKeyboardState(NULL);
              //   if(event.type == SDL_KEYDOWN) {
              //     if (keystate[SDL_SCANCODE_A]) {
              //       action_registered = true;
              //       //board.movePlayer(0, 0, 100);
              //       (*music)[1];
              //     }
              //     else if (keystate[SDL_SCANCODE_D]) {
              //       action_registered = true;
              //       //board.movePlayer(0, 1, 100);
              //       (*music)[1];
              //     }
              //     else if (keystate[SDL_SCANCODE_W]) {
              //       action_registered = true;
              //       //board.movePlayer(0, 2, 100);
              //       (*music)[1];
              //     }
              //     else if (keystate[SDL_SCANCODE_S]) {
              //       action_registered = true;
              //       //board.movePlayer(0, 3, 100);
              //       (*music)[1];
              //     }
              //   }
              // }
              std::cout << "human wants to shoot with bow!" << std::endl;
              //board.shootProjectile(human->getCurRow(), human->getCurCol())
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
