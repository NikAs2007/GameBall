cmake_minimum_required(VERSION 3.30)
project(GameBall)

set(SFML_DIR "D:/SFML/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} main.cpp Enemy.cpp Player.cpp Camera.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
