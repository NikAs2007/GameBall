cmake_minimum_required(VERSION 3.5)
project(GameBall)

set(SN "${PROJECT_NAME}server")
set(CN "${PROJECT_NAME}client")

if(WIN32)
	set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.2_win/lib/cmake/SFML")
endif()

if(UNIX)
	set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.2_lin/lib/cmake/SFML")
endif()

#set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.2_win/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)


add_executable(${SN} server/main.cpp GameBallLib/Enemy.cpp GameBallLib/Player.cpp GameBallLib/Camera.cpp GameBallLib/Menu.cpp)
set_target_properties(${SN} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#set_target_properties(${SN} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
target_link_libraries(${SN} PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(${SN} PRIVATE libs/asio-1.36.0/include)

add_executable(${CN} client/main.cpp GameBallLib/Enemy.cpp GameBallLib/Player.cpp GameBallLib/Camera.cpp GameBallLib/Menu.cpp)
set_target_properties(${CN} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
target_link_libraries(${CN} PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(${CN} PRIVATE libs/asio-1.36.0/include)
