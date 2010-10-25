#include "BoardGraphicsComponent.h"
#include "BackgroundSprite.h"
#include "GameEngine.h"
#include "GameState.h"
#include "GameBoard.h"

BoardGraphicsComponent::BoardGraphicsComponent( GameBoard *board, GameEngine *engine ):
  GraphicsComponent(board, engine){}

BoardGraphicsComponent::~BoardGraphicsComponent(){}

void BoardGraphicsComponent::update( GameState *obj ){

}
