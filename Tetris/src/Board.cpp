#include "Board.h"

#include <cstdio>

void Board::initBoard() {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      mBoard[i][j] = POS_FREE;
      // printf("Board initialization error at (%d, %d)\n", i, j);
    }
  }
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation) {
  for (int i_1 = pX, i_2 = 0; i_1 < pX + PIECE_BLOCKS; i_1++, i_2++) {
    for (int j_1 = pY, j_2 = 0; j_1 < pY + PIECE_BLOCKS; j_1++, j_2++) {
      if (i_1 >= 0 &&i_1 < BOARD_WIDTH && j_1 >= 0 && j_1 < BOARD_HEIGHT) {
        if (mPieces->GetBlockType(pPiece, pRotation, j_2, i_2) != BLOCK_EMPTY) {
          mBoard[i_1][j_1] = POS_FILLED;
        }
      }
    }
  }
}

bool Board::isGameOver() {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (mBoard[i][0] == POS_FILLED) {
      return true;
    }
  }
  return false;
}

void Board::DeleteLine(int pY) {
  for (int j = pY; j > 0; j--) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
      mBoard[i][j] = mBoard[i][j - 1];
    }
  }
}

bool Board::DeletePossibleLines() {
    bool lineDeleted = false;
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int i = 0;
        while (i < BOARD_WIDTH) {
            if (mBoard[i][j] == POS_FREE) break;
            i++;
        }
        if (i == BOARD_WIDTH) {
            DeleteLine(j);
            lineDeleted = true;
            j--;
        }
    }
    return lineDeleted;
}

bool Board::isFreeBlock(int pX, int pY) {
  if (mBoard[pX][pY] == POS_FREE) return true;
  return false;
}

int Board::GetXPosInPixels(int pPos) {
  return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) +
          (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pPos) {
  return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Board::isPossibleMovement(int pX, int pY, int pPiece, int pRotation) {
  for (int i_1 = pX, i_2 = 0; i_1 < pX + PIECE_BLOCKS; i_1++, i_2++) {
    for (int j_1 = pY, j_2 = 0; j_1 < pY + PIECE_BLOCKS; j_1++, j_2++) {
      if (i_1 < 0 || i_1 > BOARD_WIDTH - 1 || j_1 > BOARD_HEIGHT - 1) {
        if (mPieces->GetBlockType(pPiece, pRotation, j_2, i_2) != BLOCK_EMPTY)
          return false;
      }
      if (j_1 > 0 &&
          (mPieces->GetBlockType(pPiece, pRotation, j_2, i_2) != BLOCK_EMPTY) &&
          (!isFreeBlock(i_1, j_1)))
        return false;
    }
  }
  return true;
}
