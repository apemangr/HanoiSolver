cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(HanoiSolver VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SDL2 library
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

# Add the source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_ttf include dirs: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf libraries: ${SDL2_TTF_LIBRARIES}")

# Add the executable
add_executable(HanoiSolver ${SOURCES})

# Link SDL2 library
target_link_libraries(HanoiSolver SDL2::SDL2 SDL2_ttf::SDL2_ttf)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
