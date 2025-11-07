#pragma once
#ifndef __SHOWTEXT_
#define __SHOWTEXT_

#include "Game.h"

class Show {
 public:
   Show(IO* mIO, Game* mGame, Board* mBoard, Pieces* mPieces, int mScreenHeight,bool runing)
     :mIO(mIO),mGame(mGame),mBoard(mBoard),mPieces(mPieces),mScreenHeight(mScreenHeight),runing(runing){}

  void ShowGameOverScreen(IO& mIO, Game& mGame, bool& running);
  void Show_operator(IO& mIO);
  void ResetGame(Game& mGame, Board& mBoard, Pieces& mPieces,
                 int mScreenHeight);
  void ShowScore(IO& mIO, Game& mGame, unsigned int& Score);

 private:
  IO* mIO;
  Game* mGame;
  bool runing = false;
  Board* mBoard;
  Pieces* mPieces;
  int mScreenHeight;
};

#endif
