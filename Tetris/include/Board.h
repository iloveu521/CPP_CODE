#ifndef _BOARD_
#define _BOARD_

//=================================
#include "Pieces.h"

//=================================

#define BOARD_LINE_WIDTH 6  // width of each of the two lines delimit the board
#define BLOCK_SIZE 32       // width and height of the board in blocks
#define BOARD_POSITION 640  // center position of the board in the window
#define BOARD_WIDTH 16
#define BOARD_HEIGHT 35
#define MIN_VERTICAL_MARGIN \
  40  // minimum vertical margin between the board and the window border
#define MIN_HORIZONTAL_MARGIN \
  40  // minimum horizontal margin between the board and the window border
#define PIECE_BLOCKS 5
#define BLOCK_EMPTY 0

//=================================

//---------------------------------
// Board
//---------------------------------

class Board {
 public:
  Board(Pieces* pPieces, int pScreenHeight)
      : mPieces(pPieces), mScreenHeight(pScreenHeight) {}

  int GetXPosInPixels(int pPos);
  int GetYPosInPixels(int pPos);
  bool isFreeBlock(int pX, int pY);
  bool isPossibleMovement(int pX, int pY, int pPiece, int pRotation);
  void StorePiece(int pX, int pY, int pPiece, int pRotation);
  bool DeletePossibleLines();
  bool isGameOver();
  void initBoard();

 private:
  enum { POS_FREE = 0, POS_FILLED = 1 };
  int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
  Pieces* mPieces;
  int mScreenHeight;

  void DeleteLine(int pY);
};
#endif  // !_BOARD_
