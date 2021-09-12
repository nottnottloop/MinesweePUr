#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <ctype.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "Text.hpp"

std::vector<SDL_Color> COLOR_VECTOR = {NEW_BACKGROUND, CLASSIC_BACKGROUND, {8, 141, 165}, RED, GREEN, BLUE, CYAN, PEACH, PURPLE, ORANGE_RED, WHITE, BLACK, PASTEL_BLUE, LIME_GREEN};
//std::vector<SDL_Color> COLOR_VECTOR = {CLASSIC_BACKGROUND, {8, 141, 165}, {64, 114, 148}};

//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

//DEBUG
//#define DEBUG_MINES 1 
//#define DEBUG_LEADERBOARD

Uint32 start_time;
Uint32 current_time;

bool entering_highscore = false;
bool highscore_entered = false;
bool highscore_tracking = true;
std::string name_string;
int time_elapsed = 0;

RenderWindow window = RenderWindow("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");
SDL_Texture* awesome = window.loadTexture("res/awesome.png");
SDL_Texture* demoawesome = window.loadTexture("res/demoawesome.png");
SDL_Texture* sunglassesawesome = window.loadTexture("res/sunglassesawesome.png");
SDL_Texture* vol = window.loadTexture("res/vol.png");
SDL_Texture* leaderboard_img = window.loadTexture("res/leaderboard.png");

Text text({650, 40}, {0, 0}, 75);
Text mines_remaining_text({10, 75}, {0, 0}, 62);
//Remaining: 99
char mines_remaining_text_chars[30] = {};
Text timer_text({195, 3}, {0, 0}, 55);
//Time: 000
char timer_text_chars[30] = {};

Text new_highscore_text({190, 10}, {0, 0}, 40);
Text name_text({SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - 40}, {0, 0}, 100);

Mix_Chunk* click;
Mix_Chunk* kaboom;
Mix_Chunk* hellyeah;
std::vector<Button*> buttons;

int current_level = 0;
int current_bg_color = 0;

struct Score {
	char name[21];
	int score;
};

void addHighScore(char name[30], int val) {
	std::ifstream ifile("highscore.bin", std::ios::binary | std::ios::in);
	Score score_array[3][5];
	ifile.read(reinterpret_cast<char*>(&score_array), sizeof(score_array));

	Score new_score_array[3][5];
	memcpy_s(new_score_array, sizeof(new_score_array), score_array, sizeof(score_array));

	ifile.close();
	std::ofstream file("highscore.bin", std::ios::out | std::ios::trunc);

	bool inserted = false;
	std::vector<Score> queue;
	for (int j = 0; j < 3; ++j) {
		if (j == current_level) {
			for (int i = 0; i < 5; ++i) {
				if (val < score_array[current_level][i].score && !inserted) {
					inserted = true;
					Score old;
					strcpy_s(old.name, score_array[current_level][i].name);
					old.score = score_array[current_level][i].score;
					Score new_score;
					strcpy_s(new_score.name, name);
					new_score.score = val;
					queue.push_back(new_score);
					if (i != 4) {
						queue.push_back(old);
					}
				} else if (inserted && i == 4) {
					break;
				} else {
					queue.push_back(score_array[current_level][i]);
				}
			}
		} else {
			for (int i = 0; i < 5; ++i) {
				queue.push_back(score_array[j][i]);
			}
		}
	}
	
	if (inserted) {
		int iterate = 0;
		for (int j = 0; j < 3; ++j) {
			for (int i = 0; i < 5; ++i) {
				strcpy_s(new_score_array[j][i].name, queue[iterate].name);
				new_score_array[j][i].score = queue[iterate].score;
				iterate++;
			}
		}
	}
	file.write(reinterpret_cast<char*>(&new_score_array), sizeof(new_score_array));
	file.close();
	highscore_entered = true;
}

void initHighScore(bool force = false) {
	std::ifstream ifile("highscore.bin", std::ios::binary | std::ios::in);
	if (!ifile.is_open() || force) {
		std::ofstream file("highscore.bin", std::ios::binary | std::ios::trunc);
		Score score_array[3][5];
		for (int j = 0; j < 3; ++j) {
			for (int i = 0; i < 5; ++i) {
				strcpy_s(score_array[j][i].name, "Anonymous");
				score_array[j][i].score = 999;
			}
		}
	file.write(reinterpret_cast<char*>(&score_array), sizeof(score_array));
	file.close();
	}
	ifile.close();
}

int loadHighScore(bool messagebox) {
	std::ifstream file("highscore.bin", std::ios::binary | std::ios::in);
	Score score_array[3][5];
	file.read(reinterpret_cast<char*>(&score_array), sizeof(score_array));
	char score_chars[300] = {};
	int worst_score = score_array[current_level][0].score;
	for (int i = 0; i < 5; ++i) {
		if (worst_score < score_array[current_level][i].score) {
			worst_score = score_array[current_level][i].score;
		}
		char temp[40];
		sprintf_s(temp, "%d. %s, %d\n", i + 1, score_array[current_level][i].name, score_array[current_level][i].score);
		strcat_s(score_chars, temp);
	}
	if (messagebox) {
		const SDL_MessageBoxButtonData message_box_buttons[] = {
			//{ /* .flags, .buttonid, .text */        0, 0, "no" },
			//{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
			//{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" },
			{ /* .flags, .buttonid, .text */        0, 1, "Highscores on" },
			{ /* .flags, .buttonid, .text */        0, 2, "Highscores off" },
		};

    SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };

		char title_buffer[30] = {};
		switch (current_level) {
			case 0:
				strcat_s(title_buffer, "Beginner");
				break;
			case 1:
				strcat_s(title_buffer, "Medium");
				break;
			case 2:
				strcat_s(title_buffer, "Expert");
				break;
		}
		strcat_s(title_buffer, " Highscores!");

		SDL_MessageBoxData message_box_data = {
				SDL_MESSAGEBOX_INFORMATION, /* .flags */
				nullptr, /* .window */
				title_buffer, /* .title */
				score_chars, /* .message */
				SDL_arraysize(message_box_buttons), /* .numbuttons */
				message_box_buttons, /* .buttons */
				&colorScheme /* .colorScheme */
		};

		int button_id;
    if (SDL_ShowMessageBox(&message_box_data, &button_id) < 0) {
			printf("error displaying message box");
    }
    if (button_id == -1) {
			printf("no selection");
    } else if (button_id == 1) {
			highscore_tracking = true;
    } else if (button_id == 2) {
			highscore_tracking = false;
    }
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Highscores!", score_chars, nullptr);
	}
	file.close();
	return worst_score;
}

void restartButtonOffset(int level, Button& restart_button) {
	switch (level) {
		case 0:
			restart_button.setOffset({0, 15});
			break;
		case 1:
		case 2:
			restart_button.setOffset({0, 5});
			break;
	}
}
void switchLevel(int level, Game& game, Text& text, Text& mines_remaining_text, Text& timer_text, Button& restart_button) {
	start_time = SDL_GetTicks();
	switch (level) {
		case 0:
			current_level = 0;
			highscore_entered = false;
			text.loadFontTexture(GREEN, "Beginner");
			text.setOffset({0, 0});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(9, 9, DEBUG_MINES);
			#else
				game.setBoard(9, 9, 10);
			#endif
			restartButtonOffset(level, restart_button);
			game.setCellScale(1.0f);
			game.setOffset({-30, 20});
			game.initBoard();
			game.generateBoard();
			break;
		case 1:
			current_level = 1;
			highscore_entered = false;
			text.loadFontTexture(CYAN, "Medium");
			text.setOffset({0, -10});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(16, 16, DEBUG_MINES);
			#else
				game.setBoard(16, 16, 40);
			#endif
			restartButtonOffset(level, restart_button);
			game.setCellScale(0.6f);
			game.setOffset({0, 60});
			game.initBoard();
			game.generateBoard();
			break;
		case 2:
			current_level = 2;
			highscore_entered = false;
			text.loadFontTexture(RED, "Expert");
			text.setOffset({0, -10});
			game.clearBoard();
			#ifdef DEBUG_MINES
				game.setBoard(16, 30, DEBUG_MINES);
			#else
				game.setBoard(16, 30, 99);
			#endif
			restartButtonOffset(level, restart_button);
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
					} else if (i < 5 && i > 1) {
						switchLevel(i - 2, game, text, mines_remaining_text, timer_text, restart_button);
						game.restart();
					} else if (i == 5) {
						loadHighScore(true);
					}
				} else {
					buttons[i]->leftClick();
					//it's like i went to Italy and had an extra large serving
					if (i == 0) {
						switchLevel(current_level, game, text, mines_remaining_text, timer_text, restart_button);
					} else if (i < 5 && i > 1) {
						switchLevel(i - 2, game, text, mines_remaining_text, timer_text, restart_button);
						game.restart();
					} else if (i == 5) {
						loadHighScore(true);
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {
	initHighScore();
	SDL_StopTextInput();
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

	Button leaderboards({0, SCREEN_HEIGHT - 196.0f / 2}, {0, 0}, {0, 0, 348, 196}, {0, 0, 348, 196}, nullptr, leaderboard_img, game, nullptr);
	leaderboards.setScale(0.5f);
	buttons.push_back(&leaderboards);

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
	switchLevel(0, game, text, mines_remaining_text, timer_text, restart_button);

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
				case SDL_TEXTINPUT:
					if (entering_highscore) {
							if (event.key.keysym.sym == SDLK_BACKSPACE && !name_string.empty())  {
								name_string = name_string.substr(0, name_string.length() - 1);
								name_text.setOffset({name_text.getOffset().x + 25, 0});
								std::cout << name_string << "\n";
							} else if (event.key.keysym.sym == SDLK_RETURN && !name_string.empty()) {
									SDL_StopTextInput();
									entering_highscore = false;
									char buffer[30];
									strcpy_s(buffer, name_string.c_str());
									addHighScore(buffer, time_elapsed);
									name_string.clear();
									name_text.setOffset({0, 0});
								} else if (name_string.length() < 20 && !event.key.repeat) {
									if (isalnum(event.text.text[0]) || isspace(event.text.text[0])) {
										name_text.setOffset({name_text.getOffset().x - 25, 0});
										name_string += event.text.text;
									}
									std::cout << name_string << "\n";
						} 
					}
					if (!entering_highscore) {
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
							case SDLK_h:
								loadHighScore(true);
								break;
							#ifdef DEBUG_LEADERBOARD 
							case SDLK_5:
								initHighScore(true);
								break;
							case SDLK_7:
								addHighScore("john", 3);
								break;
							case SDLK_8:
								addHighScore("andrew", 5);
								break;
							case SDLK_9:
								addHighScore("frankie", 22);
								break;
							#endif
							case SDLK_1:
								switchLevel(0, game, text, mines_remaining_text, timer_text, restart_button);
								break;
							case SDLK_2:
								switchLevel(1, game, text, mines_remaining_text, timer_text, restart_button);
								break;
							case SDLK_3:
								switchLevel(2, game, text, mines_remaining_text, timer_text, restart_button);
								break;
						}
					}
		}
		}
		if (!entering_highscore) {
			//get time for time elapsed in game
			current_time = SDL_GetTicks();

			//begin render loop
			for (int i = 0; i < buttons.size(); ++i) {
				//this isn't great, but we live and learn
				if (i == 0 && game.getLose()) {
					buttons[0]->setFgTex(demoawesome);
					restart_button.setScale(0.15);
					restartButtonOffset(current_level, restart_button);
					restart_button.offset_ = restart_button.offset_ + Vector2f{-14, -26};
				} else if (i == 0 && game.getWin()) {
					buttons[0]->setFgTex(sunglassesawesome);
					restart_button.setScale(0.125f);
					restartButtonOffset(current_level, restart_button);
				} else {
					buttons[0]->setFgTex(awesome);
					restart_button.setScale(0.125f);
					restartButtonOffset(current_level, restart_button);
				}
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

			mines_remaining_text.loadFontTexture(LIME_GREEN, mines_remaining_text_chars);
			window.render(mines_remaining_text);

			if (!game.getWin()) {
				time_elapsed = (current_time - start_time) / 1000;
			} else if (!highscore_entered && loadHighScore(false) > time_elapsed && highscore_tracking) {
				entering_highscore = true;
				SDL_StartTextInput();
			}
			if (time_elapsed < 999) {
				sprintf_s(timer_text_chars, "Time: %03d", time_elapsed);
			} else {
				sprintf_s(timer_text_chars, "Time: 999");
			}
			timer_text.loadFontTexture(ORANGE_RED, timer_text_chars);
			game.renderBoard();
		} else {
			new_highscore_text.loadFontTexture(WHITE, "New highscore! Enter name below:");
			window.render(new_highscore_text);
			name_text.loadFontTexture(WHITE, name_string.c_str());
			window.render(name_text);
		}
		if (entering_highscore) {
			timer_text.setPos({SCREEN_WIDTH / 2.0f - 135, 100});
		} else {
			timer_text.setPos({195, 3});
		}
		window.render(timer_text);
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