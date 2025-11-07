#include "ShowText.h"
#include "IO.h"

#include <vector>

void Show::ShowGameOverScreen(IO& mIO, Game& mGame, bool& running) {
  bool waitingForKey = true;

  while (waitingForKey) {
    // 清屏
    mIO.ClearScreen();

    // 绘制最后的游戏场景（作为背景）
    mGame.DrawScene();

    // 获取屏幕尺寸
    int screenWidth = mIO.GetScreenWidth();
    int screenHeight = mIO.GetScreenHeight();

    // 绘制 "GAME OVER!" 大字
    std::string gameOverText = "GAME OVER!";
    int textWidth = gameOverText.length() * 20;
    int x = (screenWidth - textWidth) / 2;
    int y = screenHeight / 2 - 50;
    mIO.DrawLargeText(x, y, gameOverText, RED);

    // 绘制选项
    std::string restartText = "Press R to restart";
    textWidth = restartText.length() * 8;
    x = (screenWidth - textWidth) / 2;
    y = screenHeight / 2 + 20;
    mIO.DrawText(x, y, restartText, GREEN, 8);

    std::string quitText = "Press Q to quit";
    textWidth = quitText.length() * 8;
    x = (screenWidth - textWidth) / 2;
    y = screenHeight / 2 + 40;
    mIO.DrawText(x, y, quitText, GREEN, 8);

    // 更新屏幕
    mIO.UpdateScreen();

    // 检查按键
    int key = mIO.Pollkey();
    if (key == SDLK_R) {  // 按R重新开始
      waitingForKey = false;
      running = true;                                  // 继续游戏循环
    } else if (key == SDLK_Q || key == SDLK_ESCAPE) {  // 按Q或ESC退出
      waitingForKey = false;
      running = false;  // 退出游戏循环
    }

    // 短暂延迟以减少CPU占用
    SDL_Delay(50);
  }
}

void Show::ResetGame(Game& mGame, Board& mBoard, Pieces& mPieces, int mScreenHeight) {
  mBoard.initBoard();

  mGame.InitGame();

  printf("Game reset - new game started\n");
}

void Show::Show_operator(IO& mIO) {
  // 清屏
  mIO.ClearScreen();

  int screenWidth = mIO.GetScreenWidth();
  int screenHeight = mIO.GetScreenHeight();

  std::vector<std::string> controlLines = {
      "Controls:",
      u8"← → : Move Left/Right",    // Unicode 左箭头和右箭头
      u8"↓    : Move Down Faster",  // Unicode 下箭头
      "Z     : Rotate Piece",
      "X     : Hard Drop",
      "ESC   : Quit Game",
      "",
      "Press any key to start"};

  // 计算文本高度和位置
  int lineHeight = 20;  // 每行高度
  int totalHeight = controlLines.size() * lineHeight;
  int startY = (screenHeight - totalHeight) / 2;

  // 逐行绘制文本
  for (size_t i = 0; i < controlLines.size(); i++) {
    std::string line = controlLines[i];
    int textWidth = line.length() * 10;  // 估算宽度（中文需要更多空间）
    int x = screenWidth / 2 - 200;
    int y = startY + (i * lineHeight + 40);

    mIO.DrawText(x, y, line, WHITE, 128);
  }

  mIO.UpdateScreen();

  // 等待用户按键
  bool waiting = true;
  while (waiting) {
    int key = mIO.Pollkey();
    if (key != -1) {
      waiting = false;
    }
    SDL_Delay(50);
  }
}

void Show::ShowScore(IO& mIO, Game& mGame, unsigned int& Score) {
  std::string scoreText = "Score: " + std::to_string(Score);
  mIO.DrawText(1000, 200, scoreText, RED, 32);
}