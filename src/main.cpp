#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "Text.hpp"

std::vector<SDL_Color> COLOR_VECTOR = {NEW_BACKGROUND, CLASSIC_BACKGROUND, {8, 141, 165}, RED, GREEN, BLUE, CYAN, PEACH, PURPLE, ORANGE_RED, WHITE, BLACK};
//std::vector<SDL_Color> COLOR_VECTOR = {CLASSIC_BACKGROUND, {8, 141, 165}, {64, 114, 148}};

//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

//DEBUG
#define DEBUG_MINES 1

Uint32 start_time;
Uint32 current_time;

bool entering_highscore = false;

RenderWindow window = RenderWindow("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");
SDL_Texture* awesome = window.loadTexture("res/awesome.png");
SDL_Texture* vol = window.loadTexture("res/vol.png");

Text text({650, 40}, {0, 0}, 75);
Text mines_remaining_text({10, 75}, {0, 0}, 62);
//Remaining: 99
char mines_remaining_text_chars[30] = {};
Text timer_text({195, 3}, {0, 0}, 55);
//Time: 000
char timer_text_chars[30] = {};

Text new_highscore_text({120, 10}, {0, 0}, 40);
Text name_text({SCREEN_WIDTH / 2.0f, 50}, {0, 0}, 40);
char name_text_chars[21] = {};

Mix_Chunk* click;
Mix_Chunk* kaboom;
Mix_Chunk* hellyeah;
std::vector<Button*> buttons;

int current_level = 1;
int current_bg_color = 0;

struct Score {
	char name[20];
	int score;
};

void initHighScore() {
	std::ifstream ifile("highscore.bin");
	if (!ifile.is_open()) {
		std::ofstream file("highscore.bin");
		Score score_array[5];
		for (int i = 0; i < 5; ++i) {
			strcpy_s(score_array[i].name, "Anonymous");
			score_array[i].score = 999;
		}
		file.write(reinterpret_cast<char*>(&score_array), sizeof(score_array));
		file.close();
	}
	ifile.close();
}

void loadHighScore() {
	std::ifstream file("highscore.bin");
	Score score_array[5];
	file.read(reinterpret_cast<char*>(&score_array), sizeof(score_array));
	char score_chars[100] = {};
	for (int i = 0; i < 5; ++i) {
		char temp[20];
		sprintf_s(temp, "%d. %s, %d\n", i + 1, score_array[i].name, score_array[i].score);
		strcat_s(score_chars, temp);
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Highscores", score_chars, nullptr);
	file.close();
}

void addHighScore(char name[20], int val) {
	std::ifstream ifile("highscore.bin");
	Score score_array[5];
	ifile.read(reinterpret_cast<char*>(&score_array), sizeof(score_array));

	Score new_score_array[5];
	memcpy_s(new_score_array, sizeof(new_score_array), score_array, sizeof(score_array));

	ifile.close();
	std::ofstream file("highscore.bin", std::ios::trunc);

	bool inserted = false;
	std::vector<Score> queue;
	for (int i = 0; i < 5; ++i) {
		if (val < score_array[i].score && !inserted) {
			inserted = true;
			Score temp;
			strcpy_s(temp.name, name);
			temp.score = val;
			queue.push_back(temp);
		}
		queue.push_back(score_array[i]);
	}
	
	if (inserted) {
		for (int i = 0; i < 5; ++i) {
			strcpy_s(new_score_array[i].name, queue[i].name);
			new_score_array[i].score = queue[i].score;
		}
		file.write(reinterpret_cast<char*>(&new_score_array), sizeof(new_score_array));
	}
	file.close();
}

void switchLevel(int level, Game& game, Text& text, Text& mines_remaining_text, Text& timer_text, Button& restart_button) {
	start_time = SDL_GetTicks();
	switch (level) {
		case 1:
			text.loadFontTexture(GREEN, "Beginner");
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
			text.loadFontTexture(CYAN, "Medium");
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
			text.loadFontTexture(RED, "Expert");
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
					if (i == 0) {
						switchLevel(current_level, game, text, mines_remaining_text, timer_text, restart_button);
					}
					if (i < 5 && i > 1) {
						switchLevel(i - 1, game, text, mines_remaining_text, timer_text, restart_button);
					}
				} else {
					buttons[i]->leftClick();
					//it's like i went to Italy and had an extra large serving
					if (i == 0) {
						switchLevel(current_level, game, text, mines_remaining_text, timer_text, restart_button);
					}
					if (i < 5 && i > 1) {
						switchLevel(i - 1, game, text, mines_remaining_text, timer_text, restart_button);
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {
	initHighScore();
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
	if((initted & flags) != flags) {
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

	text.openFont(FONT_LOCATION, text.getSize());
	mines_remaining_text.openFont(FONT_LOCATION, mines_remaining_text.getSize());
	timer_text.openFont(FONT_LOCATION, timer_text.getSize());
	new_highscore_text.openFont(FONT_LOCATION, new_highscore_text.getSize());
	name_text.openFont(FONT_LOCATION, name_text.getSize());


	bool quit = false;
	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();
	text.loadFontTexture(GREEN, "Beginner");

	//set the game to beginner on startup
	switchLevel(1, game, text, mines_remaining_text, timer_text, restart_button);

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (!entering_highscore) {
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
					}
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_r:
							switchLevel(current_level, game, text, mines_remaining_text, timer_text, restart_button);
							break;
						case SDLK_c:
							if (current_bg_color < COLOR_VECTOR.size() - 1) {
								++current_bg_color;
							} else {
								current_bg_color = 0;
							}
							break;
						case SDLK_1:
							switchLevel(1, game, text, mines_remaining_text, timer_text, restart_button);
							break;
						case SDLK_2:
							switchLevel(2, game, text, mines_remaining_text, timer_text, restart_button);
							break;
						case SDLK_3:
							switchLevel(3, game, text, mines_remaining_text, timer_text, restart_button);
							break;
					}
			}
		}
		if (!entering_highscore) {
			//get time for time elapsed in game
			current_time = SDL_GetTicks();

			//begin render loop
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
			//beginner, medium, expert
			window.render(text);
			sprintf_s(mines_remaining_text_chars, "Remaining: %d", game.getRemaining());

			mines_remaining_text.loadFontTexture(PEACH, mines_remaining_text_chars);
			window.render(mines_remaining_text);

			int time_elapsed;
			if (!game.getWin()) {
				time_elapsed = (current_time - start_time) / 1000;
			} else {
				entering_highscore = true;
			}
			if (time_elapsed < 999) {
				sprintf_s(timer_text_chars, "Time: %03d", time_elapsed);
			} else {
				sprintf_s(timer_text_chars, "Time: 999");
			}
			timer_text.loadFontTexture(ORANGE_RED, timer_text_chars);
			window.render(timer_text);
			game.renderBoard();
		} else {
			new_highscore_text.loadFontTexture(WHITE, "New highscore! Enter name below (max 20)");
			window.render(new_highscore_text);
			window.render(name_text);
		}
		window.display();
		window.clear(COLOR_VECTOR[current_bg_color], 0xFF);
		window.showWindow();
	}

	window.cleanUp();
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}