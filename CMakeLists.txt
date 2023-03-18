cmake_minimum_required (VERSION 3.1)

project(game)


set(SFML_STATIC_LIBRARIES TRUE)


set (SFML_DIR "C:/Users/olga4/Desktop/SFML-2.5.1/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(game  game1.cpp)
target_link_libraries(game sfml-graphics)