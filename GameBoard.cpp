#include "GameBoard.hpp"

GameBoard::GameBoard(){
  setupBoard();
}

GameBoard::GameBoard( GameBoard const &b ){
  setupBoard();

  for ( int i=0; i<_rows; i++) {
    for ( int j=0; j<_columns; j++) {
      markSquare( j, i, b.getSquare( j, i ) );
    }
  }

}

GameBoard::~GameBoard(){
  for ( int i=0; i<_rows; i++ ) {
    delete [] _board[i];
  }
  delete _board;
}

void GameBoard::setupBoard(){
  //allocate
  _board = new Values::Players*[_rows];

  for ( int i=0; i<_rows; i++ ){ 
    _board[i] = new Values::Players[_columns];
    // initialize
    for ( int j=0; j<_columns; j++ ) {
      _board[i][j] = Values::PLAYER_NULL;
    }
  }
}

bool GameBoard::markSquare( int x, int y, Values::Players player ){
  if ( x >= 0 && x < _columns &&
       y >= 0 && y < _rows &&
       player != Values::PLAYER_NULL &&
       _board[y][x] == Values::PLAYER_NULL ){
    _board[y][x] = player;
    return true;
  } else {
    return false;
  }
}

Values::Players GameBoard::getSquare( int x, int y ) const{
  return _board[y][x];
}

int GameBoard::getRows() const{
  return _rows;
}

int GameBoard::getColumns() const{
  return _columns;
}

Values::WinState GameBoard::checkGameWon(){
  // needed to see if there is a draw
  bool foundNull = false;

  Values::WinState win = Values::WIN_NULL;

  win = checkColumns(foundNull);
  if ( win != Values::WIN_NULL ){
    return win;
  }
  
  win = checkRows(foundNull);
  if ( win != Values::WIN_NULL ){
    return win;
  }

  win = checkLRDiagonal(foundNull);
  if ( win != Values::WIN_NULL ){
    return win;
  }

  win = checkRLDiagonal(foundNull);
  if ( win != Values::WIN_NULL ){
    return win;
  }

  if ( !foundNull ){
    return Values::WIN_TIE;
  }

  return win;
}


Values::WinState GameBoard::checkColumns( bool &foundNull ){
  // check columns
  bool columnComplete  = false;
  int lastChecked = 0;
  
  for ( int i=0; i<_rows; i++ ){
    for ( int j=0; j<_columns; j++ ) {
      if ( i==0 ){
	// if in the first spot in a column
	if ( _board[i][j] != Values::PLAYER_NULL ) {
	  // check to see if this player owns this column
	  lastChecked = _board[i][j];
	} else {
	  foundNull = true;
	  // check the next column
	  break;
	}
      } else {
	// does this spot match the previous in this column?
	if ( _board[i][j] == lastChecked ){
	  columnComplete = true;
	} else {
	  if ( _board[i][j] == Values::PLAYER_NULL ){
	    foundNull = true;
	  }
	  columnComplete = false;
	  break;
	}
      }
    }
  }

  if ( columnComplete ){
    switch ( lastChecked ){
      case Values::PLAYER_ONE:
	return Values::WIN_ONE;
	break;
	
      case Values::PLAYER_TWO:
	return Values::WIN_TWO;
	break;
    }
  }
  return Values::WIN_NULL;
}

Values::WinState GameBoard::checkRows( bool &foundNull ){
  // check rows
  bool rowsComplete  = false;
  int lastChecked = 0;
  
  for ( int j=0; j<_rows; j++ ){
    for ( int i=0; i<_columns; i++ ) {
      if ( j==0 ){
	// if in the first spot in a column
	if ( _board[i][j] != Values::PLAYER_NULL ) {
	  // check to see if this player owns this column
	  lastChecked = _board[i][j];
	} else {
	  foundNull = true;
	  // check the next column
	  break;
	}
      } else {
	// does this spot match the previous in this column?
	if ( _board[i][j] == lastChecked ){
	  rowsComplete = true;
	} else {
	  if ( _board[i][j] == Values::PLAYER_NULL ){
	    foundNull = true;
	  }
	  rowsComplete = false;
	  break;
	}
      }
    }
  }

  if ( rowsComplete ){
    switch ( lastChecked ){
      case Values::PLAYER_ONE:
	return Values::WIN_ONE;
	break;
	
      case Values::PLAYER_TWO:
	return Values::WIN_TWO;
	break;
    }
  }
  return Values::WIN_NULL;
}

/**
 * This is for check to see if a player has a 
 * diagonal row going from bottom left to top right.
 * 
 * Currently only works for square boards.
 */
Values::WinState GameBoard::checkLRDiagonal( bool &foundNull ){
  int lastChecked = 0;
  bool diagonalComplete = false;

  for ( int i=(_rows-1), j=0;
	i >= 0, j<_columns;
	i--, j++ ) {
    if ( i==0 && j==0 ){
      // top right position
      if ( _board[i][j] == Values::PLAYER_NULL ){
	// first position is null, so no need to continue
	lastChecked = Values::PLAYER_NULL;
	break;
      } else {
	lastChecked = _board[i][j];
      }
    } else {
      if ( _board[i][j] != lastChecked ){
	diagonalComplete = false;
	break;
      } else {
	diagonalComplete = true;
      }
    }
  }

  if ( diagonalComplete ) {
    switch ( lastChecked ){
      case Values::PLAYER_ONE:
	return Values::WIN_ONE;
	break;
	
      case Values::PLAYER_TWO:
	return Values::WIN_TWO;
	break;
    }
  }
  return Values::WIN_NULL;
}

/**
 * This is for check to see if a player has a 
 * diagonal row going from top left to bottom right.
 *
 * Right now this only works for square boards.
 */
Values::WinState GameBoard::checkRLDiagonal( bool &foundNull ){
  int lastChecked = 0;
  bool diagonalComplete = false;

  for ( int i=0, j=0;
	i<_rows, j<_columns;
	i++, j++ ) {
    if ( i==(_rows-1) && j==(_columns-1) ){
      // bottom left position
      if ( _board[i][j] == Values::PLAYER_NULL ){
	// first position is null, so no need to continue
	lastChecked = Values::PLAYER_NULL;
	break;
      } else {
	lastChecked = _board[i][j];
      }
    } else {
      if ( _board[i][j] != lastChecked ){
	diagonalComplete = false;
	break;
      } else {
	diagonalComplete = true;
      }
    }
  }

  if ( diagonalComplete ) {
    switch ( lastChecked ){
      case Values::PLAYER_ONE:
	return Values::WIN_ONE;
	break;
	
      case Values::PLAYER_TWO:
	return Values::WIN_TWO;
	break;
    }
  }
  return Values::WIN_NULL;
}
