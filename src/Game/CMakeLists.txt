add_library(game
  ComputerGame.cpp
  Maps/TestMap.hpp
  States/Character/MoveState.cpp
  States/Character/WaitState.hpp
  States/Character/NPCStandState.hpp
  States/Character/PlanStrollState.hpp
  States/TestState.cpp
)

target_include_directories(game PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(game traits engine ${SFML_LIBRARIES})
