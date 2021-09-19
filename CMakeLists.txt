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

#add_executable (MinesweePUr ${SOURCES})
add_executable (MinesweePUr WIN32 ${SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")

target_include_directories (MinesweePUr PUBLIC
	#C:/dev/Libraries/SDL2-2.0.16vc/include/SDL2
	"C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/include/SDL2"
	include
)

target_link_directories (MinesweePUr PUBLIC
	#C:/dev/Libraries/SDL2-2.0.16/lib/x64
	"C:/dev/Libraries/SDL2-2.0.16gcc/x86_64-w64-mingw32/lib"
)

target_link_libraries(MinesweePUr mingw32 SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer)