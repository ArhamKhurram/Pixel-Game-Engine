cmake_minimum_required(VERSION 3.8)
project("Too_2riyal")

include_directories(include/SDL2)
include_directories(include/imgui)
include_directories(include/Game)
link_directories(lib)

file(GLOB SRC src/*.cpp src/*.hpp src/*.h imgui/*.cpp imgui/*.hpp imgui/*.h)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()