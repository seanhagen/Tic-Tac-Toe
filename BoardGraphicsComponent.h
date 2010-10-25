#ifndef __BOARDGRAPHICSCOMPONENT_H
#define __BOARDGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"

class BoardGraphicsComponent : public GraphicsComponent {
 public:
  void update( GameState *obj );

  BoardGraphicsComponent( GameBoard *board, GameEngine *engine );
  ~BoardGraphicsComponent();
};

#endif /* __BOARDGRAPHICSCOMPONENT_H */
