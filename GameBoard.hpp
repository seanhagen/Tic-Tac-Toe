#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H

#include "enums.h"

class GameBoard {

 public:
  bool markSquare(int x, int y, Values::Players player);
  int getRows() const;
  int getColumns() const;
  Values::Players getSquare( int x, int y ) const;
  Values::WinState checkGameWon();

  GameBoard();
  GameBoard( GameBoard const &b );
  ~GameBoard();

 private:
  void setupBoard();
  Values::WinState checkColumns(bool &foundNull);
  Values::WinState checkRows(bool &foundNull);
  Values::WinState checkLRDiagonal(bool &foundNull);
  Values::WinState checkRLDiagonal(bool &foundNull);


 protected:
  Values::Players **_board;
  static const int _rows = 3;
  static const int _columns = 3;
};

#endif /* __GAMEBOARD_H */
