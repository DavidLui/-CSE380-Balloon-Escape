#pragma once
#include "balloon_escape_VS\stdafx.h"

/*
	BalloonEscapeGame.h

	This file contains setup data for making the BalloonEscape game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE IS THE BalloonEscape GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE

//LEVELS
static const wstring	W_LEVEL_1_DIR			= L"data/levels/Forest/";
static const wstring	W_LEVEL_1_NAME			= L"ForestLevel.tmx";
static const wstring	W_LEVEL_2_DIR			= L"data/levels/Sky/";
static const wstring	W_LEVEL_2_NAME			= L"SkyLevel.tmx";
static const wstring	W_LEVEL_3_DIR			= L"data/levels/Space/";
static const wstring	W_LEVEL_3_NAME			= L"SpaceLevel.tmx";


static const wstring	W_INIT_FILE				= L"data/BalloonEscapeInit.txt";
static const wstring	W_GUI_INIT_FILE			= L"data/BallonEscapeGUI.txt";
static const string		W_DEBUG_FILE			= "DebugOutput.txt";


// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE					= L"TITLE";
static const wstring	W_SCREEN_WIDTH			= L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT			= L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE	= L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE		= L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X		= L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y		= L"VIEWPORT_OFFSET_Y";
static const wstring	W_TOGGLE_OFFSET_Y		= L"TOGGLE_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED		= L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN		= L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE		= L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED			= L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN		= L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE		= L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND		= L"Go To Main Menu";
static const wstring	W_START_COMMAND			= L"Start";
static const wstring	W_EXIT_COMMAND			= L"Exit";
static const wstring	W_HELP_COMMAND			= L"Help";
static const wstring	W_ABOUT_COMMAND			= L"About";

static const wstring	W_QUIT_COMMAND			= L"Quit";
static const wstring	W_GREEN_CURSOR_PATH		= L"data/gui/cursor/green_cursor.png";
static const wstring	W_RED_CURSOR_PATH		= L"data/gui/cursor/red_cursor.png";
static const wstring	W_SPLASH_SCREEN_PATH	= L"data/gui/overlays/splash_screen_overlay.png";
static const wstring	W_VICTORY_SCREEN_PATH	= L"data/gui/overlays/victory_screen_overlay.png";
static const wstring	W_HELP_SCREEN_PATH	    = L"data/gui/overlays/help.png";
static const wstring	W_ABOUT_SCREEN_PATH	    = L"data/gui/overlays/about.png";
static const wstring	W_GAME_OVER_SCREEN_PATH	= L"data/gui/overlays/game_over_screen_overlay.png";

static const wstring	W_MAIN_MENU_PATH		= L"data/gui/overlays/main_menu_overlay.png";
static const wstring	W_START_IMAGE_PATH		= L"data/gui/buttons/start_game.png";
static const wstring	W_START_IMAGE_MO_PATH	= L"data/gui/buttons/start_game_mo.png";
static const wstring	W_EXIT_IMAGE_PATH		= L"data/gui/buttons/exit_game.png";
static const wstring	W_EXIT_IMAGE_MO_PATH	= L"data/gui/buttons/exit_game_mo.png";
static const wstring	W_QUIT_IMAGE_PATH		= L"data/gui/buttons/quit.png";
static const wstring	W_QUIT_IMAGE_MO_PATH	= L"data/gui/buttons/quit_mo.png";
static const wstring	W_HELP_IMAGE_PATH		= L"data/gui/buttons/help.png";
static const wstring	W_HELP_IMAGE_MO_PATH	= L"data/gui/buttons/help_mo.png";
static const wstring	W_ABOUT_IMAGE_PATH		= L"data/gui/buttons/about.png";
static const wstring	W_ABOUT_IMAGE_MO_PATH	= L"data/gui/buttons/about_mo.png";
// LIFE BARS
static const wstring	W_LIFEBAR_10_PATH	    = L"data/gui/lifestatus/lifebar10.png";
static const wstring	W_LIFEBAR_9_PATH	    = L"data/gui/lifestatus/lifebar9.png";
static const wstring	W_LIFEBAR_8_PATH	    = L"data/gui/lifestatus/lifebar8.png";
static const wstring	W_LIFEBAR_7_PATH	    = L"data/gui/lifestatus/lifebar7.png";
static const wstring	W_LIFEBAR_6_PATH	    = L"data/gui/lifestatus/lifebar6.png";
static const wstring	W_LIFEBAR_5_PATH	    = L"data/gui/lifestatus/lifebar5.png";
static const wstring	W_LIFEBAR_4_PATH	    = L"data/gui/lifestatus/lifebar4.png";
static const wstring	W_LIFEBAR_3_PATH	    = L"data/gui/lifestatus/lifebar3.png";
static const wstring	W_LIFEBAR_2_PATH	    = L"data/gui/lifestatus/lifebar2.png";
static const wstring	W_LIFEBAR_1_PATH	    = L"data/gui/lifestatus/lifebar1.png";
static const wstring	W_LIFEBAR_0_PATH	    = L"data/gui/lifestatus/lifebar0.png";

static const wstring	W_EXTRA_LIVES_2_PATH	= L"data/gui/lifestatus/life2.png";
static const wstring	W_EXTRA_LIVES_1_PATH	= L"data/gui/lifestatus/life1.png";
static const wstring	W_EXTRA_LIVES_0_PATH	= L"data/gui/lifestatus/life0.png";

// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";
static const wstring	JUMPING = L"JUMPING";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 20.0f;
static const float		W_GRAVITY = -0.8f;
static const float		JUMPING_BOT_MIN_CYCLES = 30;
static const float		JUMPING_BOT_MAX_CYCLES = 120;
static const float		JUMPING_BOT_MAX_VELOCITY = 40;
static const float		PLAYER_INIT_X = 80.0f;
static const float		PLAYER_INIT_Y = 100.0f;
static const float		JUMP_SPEED = 24.0f;
static const float		PLAYER_SPEED = 6.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;
static const wstring	FLYING_RIGHT(L"FLYING_RIGHT");
static const wstring	FLYING_LEFT(L"FLYING_LEFT");
static const wstring	IDLE(L"IDLE");

// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int G_KEY = (unsigned int)'G';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int T_KEY = (unsigned int)'T';
const unsigned int L_KEY = (unsigned int)'L';

const unsigned int ONE_KEY = VkKeyScan('1');
const unsigned int TWO_KEY = VkKeyScan('2');

const unsigned int THREE_KEY = VkKeyScan('3');

const unsigned int CTR_KEY = VK_CONTROL;
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';