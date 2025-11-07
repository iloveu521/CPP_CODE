#include <Windows.h>

extern int main();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow) {
  return main();
}