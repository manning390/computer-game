add_subdirectory(Traits)
add_subdirectory(Engine)
add_subdirectory(Game)

# TestVendors
add_executable(testVendors testVendors.cpp)
target_include_directories(testVendors PRIVATE "${SPDLOG_DIR}/include")
target_link_libraries(testVendors PRIVATE ${SFML_LIBRARIES})
# End TestVendors

# ComputerGame
add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_link_libraries(${PROJECT_NAME} traits engine game ${SFML_LIBRARIES})
# End ComputerGame

include(Install.cmake)
