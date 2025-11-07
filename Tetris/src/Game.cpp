#include "Game.h"

int Game::GetRand(int pA, int pB) { return rand() % (pB - pA + 1) + pA; }

void Game::InitGame() {
  srand((unsigned int)time(NULL));

  mPiece = GetRand(0, 6);
  mRotation = GetRand(0, 3);
  mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
  mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

  mNextPiece = GetRand(0, 6);
  mNextRotation = GetRand(0, 3);
  mNextPosX = BOARD_WIDTH + 5;
  mNextPosY = 5;
}

void Game::CreateNewPiece() {
  mPiece = mNextPiece;
  mRotation = mNextRotation;

  int offset_x = mPieces->GetXInitialPosition(mPiece, mRotation);
  int offset_y = mPieces->GetYInitialPosition(mPiece, mRotation);

  mPosX = (BOARD_WIDTH / 2) + offset_x;
  mPosY = offset_y;

  if (mPosY > BOARD_HEIGHT / 2) {
    if (mPosY > BOARD_HEIGHT / 2) {
      printf("WARNING: Initial Y position too low (%d), adjusting to -3\n",
             mPosY);
      mPosY = -3;
    }
  }

   printf("Initial position: (%d, %d)\n", mPosX, mPosY);

  if (!mBoard->isPossibleMovement(mPosX, mPosY, mPiece, mRotation)) {
    printf("WARNING: Invalid initial position! Trying to adjust...\n");
    }

    for (int tryY = mPosY - 1; tryY >=-3; tryY--) {
      if (mBoard->isPossibleMovement(mPosX, tryY, mPiece, mRotation)) {
        mPosY = tryY;
        printf("Adjusted to valid position: (%d, %d)\n", mPosX, mPosY);
        break;
      }
    }


  mNextPiece = GetRand(0, 6);
  mNextRotation = GetRand(0, 3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
  if (pPiece < 0 || pPiece > 6 || pRotation < 0 || pRotation > 3) {
    fprintf(stderr, "Invalid piece parameters: piece=%d, rotation=%d\n", pPiece,
            pRotation);
    return;
  }
  color mColor = GREEN;

  int mPixelsX = mBoard->GetXPosInPixels(pX);
  int mPixelsY = mBoard->GetYPosInPixels(pY);

  for (int i = 0; i < PIECE_BLOCKS; i++) {
    for (int j = 0; j < PIECE_BLOCKS; j++) {
      int blockType = mPieces->GetBlockType(pPiece, pRotation, j, i);
      if (blockType < 0 || blockType > 2) {
        fprintf(stderr, "Invalid block type: %d\n", blockType);
        continue;
      }
      if (blockType != 0) {
        mColor = (blockType == 2) ? BLUE : GREEN;

        mIO->DrawRectangle(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE,
                           (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                           (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                           mColor);
      }
    }
  }
}

void Game::DrawBoard() {
  int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
  int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
  int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

  mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
  mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

  mX1 += 1;
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!mBoard->isFreeBlock(i, j)) {
        mIO->DrawRectangle(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
                           (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                           (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
      }
    }
  }
}

void Game::DrawScene() {
  DrawBoard();
  DrawPiece(mPosX, mPosY, mPiece, mRotation);
  DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}
