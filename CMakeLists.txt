cmake_minimum_required (VERSION 3.12)

project ("MinesweePUr")

set (SOURCES
	src/main.cpp
	src/renderwindow.cpp
	src/cell.cpp
	src/entity.cpp
)

add_executable (MinesweePUr ${SOURCES})
# add_executable (MinesweePUr+ WIN32 ${SOURCES})

target_include_directories (MinesweePUr PUBLIC
	C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/include/SDL2
	include
)

target_link_directories (MinesweePUr PUBLIC
	C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/lib
)

target_link_libraries(MinesweePUr mingw32 SDL2main SDL2 SDL2_image)