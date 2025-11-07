#include "Game.h"
#include "ShowText.h"

const unsigned long INITIAL_WAIT_TIME = 700; // 初始速度（ms）
const unsigned long MIN_WAIT_TIME = 100;     // 最快速度（ms）
unsigned long waitTime = INITIAL_WAIT_TIME;

int main() {
  printf("Starting Tetris...\n");

  IO mIO;
  if (!mIO.InitGraph()) {
    fprintf(stderr, "Failed to initialize graphics\n");
    return -1;
  }
  printf("Graphics initialized successfully\n");

  int mScreenHeight = mIO.GetScreenHeight();
  printf("Screen height: %d\n", mScreenHeight);

  // Pieces
  Pieces mPieces;
  printf("Pieces created\n");

  // Board
  Board mBoard(&mPieces, mScreenHeight);
  printf("Board created\n");

  // Game
  Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);
  printf("Game initialized\n");

  bool running = true;
  Show mShow(&mIO, &mGame, &mBoard, &mPieces, mScreenHeight, running);

  mShow.Show_operator(mIO);
  // Get the actual clock milliseconds (SDL)
  unsigned long mTime1 = SDL_GetTicks();
  // unsigned long frameCount = 0;
  unsigned int mScore = 0;
  int mNum = 0;
  // ----- Main Loop -----
  while (running) {
    // ----- Draw -----
    // frameCount++;

    // if (frameCount % 100 == 0) {
    //   printf("Frame: %lu, Pos: (%d, %d), Piece: %d, Rotation: %d\n",
    //   frameCount,
    //          mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
    // }

    mIO.ClearScreen();   // Clear screen
    mGame.DrawScene();   // Draw staff
    mShow.ShowScore(mIO, mGame,mScore);
    mIO.UpdateScreen();  // Put the graphic context in the screen

    // ----- Input -----

    int mKey = mIO.Pollkey();

    switch (mKey) {
      case (SDLK_RIGHT): {
        if (mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY,
                                      mGame.mPiece, mGame.mRotation))
          mGame.mPosX++;
        break;
      }

      case (SDLK_LEFT): {
        if (mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY,
                                      mGame.mPiece, mGame.mRotation))
          mGame.mPosX--;
        break;
      }

      case (SDLK_DOWN): {
        if (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1,
                                      mGame.mPiece, mGame.mRotation))
          mGame.mPosY++;
        break;
      }

      case (SDLK_X): {
        // Check collision from up to down
        while (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                                         mGame.mRotation)) {
          mGame.mPosY++;
        }

        mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece,
                          mGame.mRotation);

        if (mBoard.DeletePossibleLines()) {
          mNum++;
          if (mNum % 3 == 0) {
            mScore *= 2;
          }
          else {
          mScore += 50;
          }
          if (mNum % 3 == 0 && waitTime > MIN_WAIT_TIME) {
            waitTime -= 100;  // 每次减少50ms
            if (waitTime < MIN_WAIT_TIME) waitTime = MIN_WAIT_TIME;
          }
        }

        if (mBoard.isGameOver()) {
          running = false;
          mShow.ShowGameOverScreen(mIO, mGame, running);
          if (running) {
            mShow.ResetGame(mGame, mBoard, mPieces, mScreenHeight);
            mTime1 = SDL_GetTicks();
            mNum = 0;
            mScore = 0;
          }
        }

        SDL_Delay(10);
        mGame.CreateNewPiece();

        if (!mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                                       mGame.mRotation)) {
          printf("ERROR: New piece at invalid position! Game Over?\n");
        }

        break;
      }

      case (SDLK_Z): {
        if (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                                      (mGame.mRotation + 1) % 4))
          mGame.mRotation = (mGame.mRotation + 1) % 4;

        break;
      }

      case (SDLK_ESCAPE): {
        running = false;
        break;
      }
    }

    // ----- Vertical movement -----

    unsigned long mTime2 = SDL_GetTicks();

    if ((mTime2 - mTime1) > waitTime) {
      if (mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece,
                                    mGame.mRotation)) {
        mGame.mPosY++;
      } else {
        mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                          mGame.mRotation);

        if (mBoard.DeletePossibleLines()) {
          mNum++;
          if (mNum % 3 == 0) {
            mScore *= 2;
          } else {
            mScore += 50;
          }
          if (mNum % 3 == 0 && waitTime > MIN_WAIT_TIME) {
            waitTime -= 100;  // 每次减少50ms
            if (waitTime < MIN_WAIT_TIME) waitTime = MIN_WAIT_TIME;
          }
        }

        if (mBoard.isGameOver()) {
          running = false;
          mShow.ShowGameOverScreen(mIO, mGame, running);
          if (running) {
            mShow.ResetGame(mGame, mBoard, mPieces, mScreenHeight);
            mTime1 = SDL_GetTicks();
            mNum = 0;
            mScore = 0;
          }
        }

        SDL_Delay(10);
        mGame.CreateNewPiece();
        if (!mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece,
                                       mGame.mRotation)) {
          printf("ERROR: New piece at invalid position! Game Over?\n");
        }
      }
      mTime1 = SDL_GetTicks();
    }
  }
  printf("Game exited normally\n");
}
