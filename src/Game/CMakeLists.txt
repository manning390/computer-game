add_library(game
  ComputerGame.cpp
  Character.hpp
  Maps/TestMap.hpp
  States/EmptyState.hpp
  States/MoveState.cpp
  States/WaitState.hpp
  States/TestState.cpp
)

target_include_directories(game PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(game traits engine ${SFML_LIBRARIES})
