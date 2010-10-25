#include "TitleGraphicsComponent.h"
#include "BackgroundSprite.h"
#include "GameEngine.h"
#include "GameState.h"
#include "GameBoard.h"

TitleGraphicsComponent::TitleGraphicsComponent( GameBoard *board, GameEngine *engine ):
  GraphicsComponent( board, engine ){}

TitleGraphicsComponent::~TitleGraphicsComponent(){
  _engine = NULL;
  _board = NULL;
}

void TitleGraphicsComponent::update( GameState *obj ){
  BackgroundSprite* background = _engine->getBackground();
  background->switchFrame( BackgroundSprite::FRAME_TITLE );
  background->update();
}
