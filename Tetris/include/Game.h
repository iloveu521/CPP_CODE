#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <cstdio>
#include <cstdlib>

#include "Board.h"
#include "IO.h"
#include "Pieces.h"
#include "time.h"

//---------------------------------
#define WAIT_TIME 700  // Number of milliseconds to wait before moving the piece down

//---------------------------------

class Game {
 public:
  Game(Board* pBoard, Pieces* pPieces, IO* pIO, int pScreenHeight) {
    if (!pBoard || !pPieces || !pIO) {
      fprintf(stderr, "Error: Null pointer passed to Game constructor\n");
      return;
    }
    mBoard = pBoard;
    mPieces = pPieces;
    mIO = pIO;
    mScreenHeight = pScreenHeight;

    InitGame();
  }
  void DrawScene();
  void CreateNewPiece();

  int mPosX, mPosY;
  int mPiece, mRotation;
  void InitGame();

 private:
  int mScreenHeight;
  int mNextPosX, mNextPosY;
  int mNextPiece, mNextRotation;

  Board* mBoard;
  Pieces* mPieces;
  IO* mIO;

  int GetRand(int pA, int pB);
  void DrawBoard();
  void DrawPiece(int pX, int pY, int pPiece, int pRotation);
};

#endif  // !_GAME_H
