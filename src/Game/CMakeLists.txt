add_library(game
  Application.cpp
  Maps/TestMap.hpp
  States/TestState.cpp
)

target_include_directories(game PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(game traits engine ImGui-SFML::ImGui-SFML)
