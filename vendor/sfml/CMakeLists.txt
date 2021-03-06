FetchContent_GetProperties(SFML)

if(NOT SFML_POPULATED)
  if (LINK_DEPS_STATIC)
    set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "")
  endif()

  set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "")

  if (USE_SYSTEM_DEPS)
    message(STATUS "Finding local SFML library v${SFML_VERSION}")
    find_package(SFML ${SFML_VERSION} COMPONENTS graphics QUIET)
  else()
    message(STATUS "Fetching SFML v${SFML_VERSION}")
    FetchContent_Populate(SFML)

    # No need to build audio and network modules
    set(SFML_BUILD_AUDIO FALSE CACHE BOOL "")
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "")
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()
