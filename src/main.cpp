#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <array>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "Text.hpp"

SDL_Color red = {255, 0, 0};
SDL_Color green = {0, 255, 0};
SDL_Color blue = {0, 0, 255};
SDL_Color cyan = {0, 255, 255};
SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};

//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

//DEBUG
//#define DEBUG_MINES 1

RenderWindow window = RenderWindow("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");
SDL_Texture* awesome = window.loadTexture("res/awesome.png");
SDL_Texture* vol = window.loadTexture("res/vol.png");

Text text({650, 40}, {0, 0});

Mix_Chunk* click;
Mix_Chunk* kaboom;
Mix_Chunk* hellyeah;
std::vector<Button*> buttons;

void switchLevel(int level, Game& game, Text& text, Button& restart_button) {
	switch (level) {
		case 1:
			text.loadFontTexture(FONT_LOCATION, FONT_SIZE, green, "Beginner");
			text.setOffset({0, 0});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(9, 9, DEBUG_MINES);
			#else
				game.setBoard(9, 9, 10);
			#endif
			restart_button.setOffset({0, 15});
			game.setCellScale(1.0f);
			game.setOffset({-30, 20});
			game.initBoard();
			game.generateBoard();
			break;
		case 2:
			text.loadFontTexture(FONT_LOCATION, FONT_SIZE, cyan, "Medium");
			text.setOffset({0, -10});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(16, 16, DEBUG_MINES);
			#else
				game.setBoard(16, 16, 40);
			#endif
			restart_button.setOffset({0, 5});
			game.setCellScale(0.6f);
			game.setOffset({0, 60});
			game.initBoard();
			game.generateBoard();
			break;
		case 3:
			text.loadFontTexture(FONT_LOCATION, FONT_SIZE, red, "Expert");
			text.setOffset({0, -10});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(16, 30, DEBUG_MINES);
			#else
				game.setBoard(16, 30, 99);
			#endif
			restart_button.setOffset({0, 5});
			game.setCellScale(0.5f);
			game.setOffset({0, 20});
			game.initBoard();
			game.generateBoard();
			break;
	}
}

void checkButtonClick(Sint32 x, Sint32 y, bool right_mouse, Game& game, Text& text, Button& restart_button) {
	for (int i = 0; i < buttons.size(); ++i) {
		if (buttons[i]->getPos().x < x && buttons[i]->getPos().x + buttons[i]->getFgFrame().w * buttons[i]->getScale() > x) {
			if (buttons[i]->getPos().y < y && buttons[i]->getPos().y + buttons[i]->getFgFrame().h * buttons[i]->getScale() > y) {
				if (right_mouse) {
					buttons[i]->rightClick();
					//it's like i went to Italy and had an extra large serving
					if (i < 5 && i > 1) {
						switchLevel(i - 1, game, text, restart_button);
					}
				} else {
					buttons[i]->leftClick();
					//it's like i went to Italy and had an extra large serving
					if (i < 5 && i > 1) {
						switchLevel(i - 1, game, text, restart_button);
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << IMG_GetError() << "\n";

	if (TTF_Init())
		std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << "\n";
		
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 0) == -1)
		std::cout << "SDL_mixer has failed. Error: " << Mix_GetError() << "\n";

	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);
	if(initted & flags != flags) {
			printf("Mix_Init: Failed to init required ogg and mod support!\n");
			printf("Mix_Init: %s\n", Mix_GetError());
	}

	Game game;

	Button restart_button({SCREEN_WIDTH / 2 - 64.0f, 0}, {0, 15}, {0, 0, 1024, 1024}, {0, 0, 1024, 1024}, nullptr, awesome, game, &Game::restart);
	restart_button.setScale(0.125f);
	buttons.push_back(&restart_button);

	Button mute_button({SCREEN_WIDTH - 128.0f, SCREEN_HEIGHT - 128.0f}, {0, 0}, {0, 0, 128, 128}, {0, 0, 128, 128}, nullptr, vol, game, &Game::toggleMute);
	buttons.push_back(&mute_button);

	Button oneBut({0, 0}, {0, 0}, {0, 0, 60, 60}, {0, 0, 60, 60}, bg, fg, game, nullptr);
	buttons.push_back(&oneBut);

	Button twoBut({60, 0}, {0, 0}, {0, 0, 60, 60}, {60, 0, 60, 60}, bg, fg, game, nullptr);
	buttons.push_back(&twoBut);

	Button threeBut({120, 0}, {0, 0}, {0, 0, 60, 60}, {120, 0, 60, 60}, bg, fg, game, nullptr);
	buttons.push_back(&threeBut);

	click = Mix_LoadWAV("res/click.ogg");
	kaboom = Mix_LoadWAV("res/kaboom.ogg");
	hellyeah = Mix_LoadWAV("res/hellyeah.ogg");

	bool quit = false;
	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();
	text.loadFontTexture(FONT_LOCATION, FONT_SIZE, green, "Beginner");

	//set the game to beginner on startup
	switchLevel(1, game, text, restart_button);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							game.checkCellClick(event.button.x, event.button.y, false);
							checkButtonClick(event.button.x, event.button.y, false, game, text, restart_button);
							break;
						case SDL_BUTTON_RIGHT:
							game.checkCellClick(event.button.x, event.button.y, true);
							checkButtonClick(event.button.x, event.button.y, true, game,text, restart_button);
							break;
					}
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_r:
							game.restart();
							break;
						case SDLK_1:
							switchLevel(1, game, text, restart_button);
							break;
						case SDLK_2:
							switchLevel(2, game, text, restart_button);
							break;
						case SDLK_3:
							switchLevel(3, game, text, restart_button);
							break;
					}
			}
		}
		for (int i = 0; i < buttons.size(); ++i) {
			//this isn't great, but we live and learn
			if (i == 1 && game.getMute()) {
				buttons[i]->setFgFrame({128, 0, 128, 128});
			} else if (i == 1) {
				buttons[i]->setFgFrame({0, 0, 128, 128});
			}
			window.render(buttons[i]->renderBgRectInfo(), buttons[i]->getBgTex());
			window.render(buttons[i]->renderFgRectInfo(), buttons[i]->getFgTex());
		}
		window.render(text);
		game.renderBoard();
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}