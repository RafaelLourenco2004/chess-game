cmake_minimum_required(VERSION 3.20)

project(ChessGame)

set(SRCS 
    src/Bishop.cpp
    src/Board.cpp
    src/King.cpp
    src/Knight.cpp
    src/main.cpp
    src/Pawn.cpp
    src/Piece.cpp
    src/Queen.cpp
    src/Rook.cpp
    src/GameRules.cpp
)


add_executable(app ${SRCS})

target_include_directories(app PRIVATE include/)