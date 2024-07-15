cmake_minimum_required(VERSION 3.5)

project(Chess)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES main.cpp Game.cpp Board.cpp Point.cpp Player.cpp Pieces/Piece.cpp Pieces/Bishop.cpp Pieces/King.cpp Pieces/Knight.cpp Pieces/Pawn.cpp Pieces/Queen.cpp Pieces/Rook.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    sfml-graphics 
    sfml-window 
    sfml-system
    -no-pie

)
