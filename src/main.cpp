#include <memory>
#include <cassert>

#include "Log.hpp"
#include "Constant.hpp"
#include "Game/Application.hpp"

#ifdef linux
int main(int argc, const char **argv)
#else
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
#endif
{
  Log::init();

  int exitCode = Engine::NoError;

  Application* app = &Application::instance();
  assert(app != nullptr && "main() Can't create Application");

  // Handle any command line arguments passed in
  //app->processArguments(argc, argv);

  //exitCode = app->run();

  //std::exit(exitCode);
}
