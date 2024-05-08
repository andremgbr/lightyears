cmake_minimum_required(VERSION 3.22.1)

project(LightYears
  VERSION 1.0.0
  LANGUAGES C CXX
)

  # create a varuable
set(LIGHT_YEARS_ENGINE_TARGET_NAME LightYearsEngine)
set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(LightYearsEngine)
add_subdirectory(LightYearsGame)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
  ${SFML_LIB_NAME}
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG 2.5.1
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})
 
