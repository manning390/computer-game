include(FetchContent)

option(USE_SYSTEM_DEPS CACHE OFF)
option(LINK_DEPS_STATIC CACHE ON)

# Don't build shared libs if we want to link to deps statically
if(LINK_DEPS_STATIC)
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUILD_SHARED_LIBS ON)
endif()

message(STATUS "Fetching third party libraries")
#=======================

set(SFML_VERSION 2.5.1)
set(IMGUI_VERSION 1.79)
set(IMGUI_SFML_VERSION 2.1)
set(SPDLOG_VERSION v1.8.2)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.5.1
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.79
)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
    GIT_TAG develop
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.8.2
)

add_subdirectory(sfml)
add_subdirectory(imgui)
add_subdirectory(imgui-sfml)

#==============
message(STATUS "Fetching thirdparty libarries done")
