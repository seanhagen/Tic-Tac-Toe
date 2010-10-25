#ifndef __TITLEGRAPHICSCOMPONENT_H
#define __TITLEGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"

class TitleGraphicsComponent : public GraphicsComponent {
 public:
  void update( GameState *obj );

  TitleGraphicsComponent( GameBoard *board, GameEngine *engine );
  ~TitleGraphicsComponent();
};

#endif /* __TITLEGRAPHICSCOMPONENT_H */
