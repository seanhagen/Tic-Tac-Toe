#include "BoardGraphicsComponent.hpp"
#include "BackgroundSprite.hpp"
#include "GameEngine.hpp"
#include "GameState.hpp"
#include "GameBoard.hpp"

BoardGraphicsComponent::BoardGraphicsComponent( GameBoard *board, GameEngine *engine ):
  GraphicsComponent(board, engine){}

BoardGraphicsComponent::~BoardGraphicsComponent(){}

void BoardGraphicsComponent::update( GameState *obj ){
  BackgroundSprite* background = _engine->getBackground();
  background->switchFrame( BackgroundSprite::FRAME_BOARD );
  background->update();
}
