#pragma once

/// Name of the author of this project
#define AUTHOR_NAME "Kirlian Silvestre"

/// Standard frame rate that each scene in the game will use
#define DEFAULT_FRAME_RATE 30

/// Pixel side size of a grid block
#define GRID_BLOCK_SIZE 32

/// Window width in pixels for beginner mode
#define BEGINNER_SCREEN_WIDTH 256
/// Window height in pixels for beginner mode
#define BEGINNER_SCREEN_HEIGHT 344
/// Window width in pixels for intermediate mode
#define INTERMEDIATE_SCREEN_WIDTH 512
/// Window height in pixels for intermediate mode
#define INTERMEDIATE_SCREEN_HEIGHT 600
/// Window width in pixels for expert mode
#define EXPERT_SCREEN_WIDTH 960
/// Window height in pixels for expert mode
#define EXPERT_SCREEN_HEIGHT 600

/// Number of grid columns for beginner mode
#define BEGINNER_GRID_COLUMNS 8
/// Number of grid rows for beginner mode
#define BEGINNER_GRID_ROWS 8
/// Number of grid columns for intermediate mode
#define INTERMEDIATE_GRID_COLUMNS 16
/// Number of grid rows for intermediate mode
#define INTERMEDIATE_GRID_ROWS 16
/// Number of grid columns for expert mode
#define EXPERT_GRID_COLUMNS 30
/// Number of grid rows for expert mode
#define EXPERT_GRID_ROWS 16

/// Number of bombs on grid for beginner mode
#define BEGINNER_NUMBER_OF_BOMBS 10
/// Number of bombs on grid for intermediate mode
#define INTERMEDIATE_NUMBER_OF_BOMBS 40
/// Number of bombs on grid for expert mode
#define EXPERT_NUMBER_OF_BOMBS 99

/// Time in seconds of pause to show the complete grid,
/// after the game is over
#define PAUSE_TIME_AFTER_GAME_END  2

/// Texture file path to block numbered 1
#define SPRITE_BLOCK_01_FILEPATH "graphics/block_1.png"
/// Texture file path to block numbered 2
#define SPRITE_BLOCK_02_FILEPATH "graphics/block_2.png"
/// Texture file path to block numbered 3
#define SPRITE_BLOCK_03_FILEPATH "graphics/block_3.png"
/// Texture file path to block numbered 4
#define SPRITE_BLOCK_04_FILEPATH "graphics/block_4.png"
/// Texture file path to block numbered 5
#define SPRITE_BLOCK_05_FILEPATH "graphics/block_5.png"
/// Texture file path to block numbered 6
#define SPRITE_BLOCK_06_FILEPATH "graphics/block_6.png"
/// Texture file path to block numbered 7
#define SPRITE_BLOCK_07_FILEPATH "graphics/block_7.png"
/// Texture file path to block numbered 8
#define SPRITE_BLOCK_08_FILEPATH "graphics/block_8.png"
/// Texture file path to block empty
#define SPRITE_BLOCK_EMPTY_FILEPATH "graphics/block_empty.png"
/// Texture file path to block hidden
#define SPRITE_BLOCK_HIDDEN_FILEPATH "graphics/block_hidden.png"
/// Texture file path to block with a bomb
#define SPRITE_BLOCK_BOMB_FILEPATH  "graphics/block_bomb.png"
/// Texture file path to block with a bomb splash
#define SPRITE_BLOCK_BOMB_SPLASH_FILEPATH  "graphics/block_bomb_splash.png"
/// Texture file path to block with a flag
#define SPRITE_BLOCK_FLAG_FILEPATH  "graphics/block_flag.png"
/// Texture file path to block with a miss flag
#define SPRITE_BLOCK_FLAG_MISS_FILEPATH  "graphics/block_flag_miss.png"

/// Texture file path to beginner button
#define SPRITE_BEGINNER_BUTTON_FILEPATH  "graphics/beginner_button.png"
/// Texture file path to intermediate button
#define SPRITE_INTERMEDIATE_BUTTON_FILEPATH  "graphics/intermediate_button.png"
/// Texture file path to expert button
#define SPRITE_EXPERT_BUTTON_FILEPATH  "graphics/expert_button.png"
/// Texture file path to game logo
#define SPRITE_LOGO_FILEPATH  "graphics/logo.png"

/// Texture name of block numbered 1 in the texture library
#define SPRITE_BLOCK_01_NAME "B01"
/// Texture name of block numbered 2 in the texture library
#define SPRITE_BLOCK_02_NAME "B02"
/// Texture name of block numbered 3 in the texture library
#define SPRITE_BLOCK_03_NAME "B03"
/// Texture name of block numbered 4 in the texture library
#define SPRITE_BLOCK_04_NAME "B04"
/// Texture name of block numbered 5 in the texture library
#define SPRITE_BLOCK_05_NAME "B05"
/// Texture name of block numbered 6 in the texture library
#define SPRITE_BLOCK_06_NAME "B06"
/// Texture name of block numbered 7 in the texture library
#define SPRITE_BLOCK_07_NAME "B07"
/// Texture name of block numbered 8 in the texture library
#define SPRITE_BLOCK_08_NAME "B08"
/// Texture name of block empty in the texture library
#define SPRITE_BLOCK_EMPTY_NAME "BEMPTY"
/// Texture name of block hidden in the texture library
#define SPRITE_BLOCK_HIDDEN_NAME "BHIDDEN"
/// Texture name of block with a bomb in the texture library
#define SPRITE_BLOCK_BOMB_NAME "BBOMB"
/// Texture name of block with a bomb splash in the texture library
#define SPRITE_BLOCK_BOMB_SPLASH_NAME "BSPLASH"
/// Texture name of block with a flag in the texture library
#define SPRITE_BLOCK_FLAG_NAME "BFLAG"
/// Texture name of block with a flag miss in the texture library
#define SPRITE_BLOCK_FLAG_MISS_NAME "BMISS"

/// Texture name of beginner button in the texture library
#define SPRITE_BEGINNER_BUTTON_NAME  "BEG_BTN"
/// Texture name of intermediate button in the texture library
#define SPRITE_INTERMEDIATE_BUTTON_NAME  "INT_BTN"
/// Texture name of expert button in the texture library
#define SPRITE_EXPERT_BUTTON_NAME  "EXP_BTN"
/// Texture name of game logo in the texture library
#define SPRITE_LOGO_NAME  "LOGO"

/// Font name of Game Sans Font in the font library
#define FONT_GAME_SANS_NAME "game_sans"
/// Font file path to the Game Sans Font
#define FONT_GAME_SANS_FILEPATH "fonts/game_sans_serif_7.ttf"
/// Font name of Jet Brains Font in the font library
#define FONT_JET_BRAINS_NAME "jet-brains"
/// Font file path to the Jet Brains Font
#define FONT_JET_BRAINS_FILEPATH "fonts/JetBrainsMono-Regular.ttf"