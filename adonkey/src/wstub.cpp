#ifdef WIN32
int main(int argc, char** argv);

#include <windows.h>  
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  return main(__argc, __argv);
}
#endif  