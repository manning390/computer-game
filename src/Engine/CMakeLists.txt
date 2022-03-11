add_library(engine
    Application.cpp
    Animation.cpp
    Atlas.cpp
    AssetProvider.hpp
    Bitmask.cpp
    EntityDef.hpp
    Entity.cpp
    Input.cpp
    IState.hpp
    Map.cpp
    StateStack.cpp
    Tween.cpp
    Util.hpp
    Window.cpp
)

target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(engine traits ${SFML_LIBRARIES})
