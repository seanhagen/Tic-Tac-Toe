#include "GameEngine.h"
#include "GameState.h"
#include "GameBoard.h"
#include "BackgroundSprite.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "TitleInputComponent.h"
#include "TitleGraphicsComponent.h"
#include "BoardInputComponent.h"
#include "BoardAIInputComponent.h"
#include "BoardGraphicsComponent.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

GameEngine::GameEngine(){
  
  srand( time(NULL) );

  _wins = 0;
  _losses = 0;
  _current_state = Values::STATE_TITLE;
  _last_state = Values::STATE_NULL;
  _current_turn = Values::TURN_ONE;
  _switch_state = false;

  _event = new SDL_Event;
  _board = new GameBoard();

  if ( SDL_Init( SDL_INIT_EVERYTHING )  != 0 ){
    cout << "Unable to initalize SDL: " << SDL_GetError() << endl;
    _current_state = Values::STATE_QUIT;
  }

  _screen = SDL_SetVideoMode( _screen_width, _screen_height, _screen_bpp, SDL_SWSURFACE );

  if ( _screen == NULL ) {
    cout << "Unable to set video mode: " << SDL_GetError() << endl;
    _current_state = Values::STATE_QUIT;
  }

  _board_offset.y = 50;

  const SDL_PixelFormat &fmt = *(_screen->format);
  _board_surface = SDL_CreateRGBSurface( SDL_SWSURFACE, _board_width, _board_height,
					 fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask );

  if ( _board_surface == NULL ) {
    cout << "Unable to create board surface: " << SDL_GetError() << endl;
    _current_state = Values::STATE_QUIT;
  }

  _background = new BackgroundSprite( _board_surface );

  SDL_WM_SetCaption( "Tic Tac Toe!", NULL );

  if ( _current_state != Values::STATE_QUIT ){
    getTitleState();
  }
}

GameEngine::~GameEngine(){
  delete _state;
  delete _event;
  delete _background;
  delete _board;
  SDL_FreeSurface( _screen );
  SDL_FreeSurface( _board_surface );
  SDL_Quit();
}

void GameEngine::gameLoop(){
  while ( _current_state != Values::STATE_QUIT ){
    checkForEvents();

    switchState();

    render();
  }
}

void GameEngine::switchState(){
  if ( _current_state != Values::STATE_NULL &&
    _switch_state == true ){
    switch ( _current_state ){
      case Values::STATE_QUIT:
	delete _state;
	break;

      case Values::STATE_TITLE:
	getTitleState();
	break;

      case Values::STATE_ABOUT:
	getAboutState();
	break;

      case Values::STATE_BOARD:
	getBoardState();
	break;

      case Values::STATE_WON:
      case Values::STATE_LOST:
	getGameOverState();
	break;
    }
    _switch_state = false;
  }
}

void GameEngine::render(){
  _state->draw();

  SDL_BlitSurface( _board_surface, NULL, _screen, &_board_offset );

  if ( SDL_Flip( _screen ) == -1 ) {
    cout << "Unable to flip screen: " << SDL_GetError() << endl;
    _current_state = Values::STATE_QUIT;
  }
}

void GameEngine::checkForEvents(){
  while ( SDL_PollEvent( _event ) ){
    if ( _event->type == SDL_QUIT ){
      _current_state = Values::STATE_QUIT;
    }

    adjustEventForBoard();

    _state->handleInput();
  }
}

void GameEngine::adjustEventForBoard(){
  switch ( _event->type ) {
    case SDL_MOUSEMOTION:
      _event->motion.x -= _board_offset.x;
      _event->motion.y -= _board_offset.y;
      break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      _event->button.x -= _board_offset.x;
      _event->button.y -= _board_offset.y;
      break;
  }
}


Values::CurrentTurn GameEngine::getCurrentTurn(){
  return _current_turn;
}

void GameEngine::setCurrentTurn( Values::CurrentTurn turn ){
  _current_turn = turn;
}

Values::States GameEngine::getCurrentState(){
  return _current_state;
}

void GameEngine::setCurrentState( Values::States state ){
  _last_state = _current_state;
  _current_state = state;
  _switch_state = true;
}

BackgroundSprite* GameEngine::getBackground(){
  return _background;
}

GameBoard* GameEngine::getGameBoard(){
  return _board;
}

void GameEngine::getTitleState(){
  delete _state;

  TitleInputComponent *i = new TitleInputComponent( _board, _event ); 
  TitleInputComponent *j = new TitleInputComponent( _board, _event ); 
  TitleGraphicsComponent *g = new TitleGraphicsComponent( _board, this );
  _state = new GameState( i, j, g, this );
}

void GameEngine::getBoardState(){
  delete _state;

  BoardInputComponent *i = new BoardInputComponent( _board, _event );
  BoardAIInputComponent *ai = new BoardAIInputComponent( _board, _event );
  BoardGraphicsComponent *g = new BoardGraphicsComponent( _board, this );
  _state = new GameState( i, ai, g, this );
}

void GameEngine::getAboutState(){
}


void GameEngine::getGameOverState(){

}
