# Name of the project
PROJECT(sdl)

# Minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Use c++ 11 standard
SET(CMAKE_CXX_STANDARD 11)

# Route to the executable and main file of the project
ADD_EXECUTABLE(${PROJECT_NAME} src/main.cpp)

# Search for packages in the system
INCLUDE(FindPkgConfig)

# System packages
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2>=2.0.0)

# Includes
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}) 

# Libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES}) 

# Execute a custom command post build to join all the .clang_complete files
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ../helpers/join_clang.sh
  )
