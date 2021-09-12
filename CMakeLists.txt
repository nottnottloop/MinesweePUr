cmake_minimum_required (VERSION 3.12)
set (CMAKE_CXX_STANDARD 17)

project ("MinesweePUr")

set (SOURCES
	src/main.cpp
	src/renderwindow.cpp
	src/cell.cpp
	src/entity.cpp
	src/game.cpp
	src/button.cpp
	src/text.cpp
)

add_executable (MinesweePUr ${SOURCES})
# add_executable (MinesweePUr WIN32 ${SOURCES})

target_include_directories (MinesweePUr PUBLIC
	C:/dev/Libraries/SDL2-2.0.16/include/SDL2
	include
)

target_link_directories (MinesweePUr PUBLIC
	C:/dev/Libraries/SDL2-2.0.16/lib/x64
)

target_link_libraries(MinesweePUr SDL2 SDL2main SDL2_image SDL2_ttf SDL2_mixer)