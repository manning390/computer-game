#include <memory>
#include <cassert>

#include "Log.hpp"
#include "Constant.hpp"
#include "Game/ComputerGame.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
  // Start logging
  Log::init();

  int exitCode = Engine::NoError;

  // Create our application singleton
  ComputerGame* app = ComputerGame::instance();
  assert(app != nullptr && "main() Can't create Application");

  // Handle any command line arguments passed in
  app->processArguments(argc, argv);

  // Run the game, when this returns the game is no longer running, duh.
  exitCode = app->run();

  // Delete the singleton and exit
  delete app;
  std::exit(exitCode);
}
