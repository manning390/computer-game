include(FetchContent)

# Options that can be set for cmake configuration
option(USE_SYSTEM_DEPS CACHE OFF)
option(LINK_DEPS_STATIC CACHE ON)


# Don't build shared libs if we want to link to deps statically
if(LINK_DEPS_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif()

message(STATUS "Fetching third party libraries")
#======================================

SET(SPDLOG_VERSION 1.8.2)
set(SFML_VERSION 2.5.1)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
  spdlog
  URL "https://github.com/gabime/spdlog/archive/v${SPDLOG_VERSION}.zip"
)

FetchContent_Declare(
  sfml
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

add_subdirectory(spdlog)
add_subdirectory(sfml)

#======================================
message(STATUS "Fetching thirdparty libraries done")
