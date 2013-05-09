#pragma once

#ifndef __GAME_INPUT_H__
#define __GAME_INPUT_H__

enum GameInput
{
	INVALID_GAME_INPUT = -1,

	GAME_INPUT_UP,
	GAME_INPUT_DOWN,
	GAME_INPUT_LEFT,
	GAME_INPUT_RIGHT,

	GAME_INPUT_NORTH,
	GAME_INPUT_NORTH_WEST,
	GAME_INPUT_WEST,
	GAME_INPUT_SOUTH_WEST,
	GAME_INPUT_SOUTH,
	GAME_INPUT_SOUTH_EAST,
	GAME_INPUT_EAST,
	GAME_INPUT_NORTH_EAST,

	GAME_INPUT_LIGHT_KICK,
	GAME_INPUT_LIGHT_PUNCH,
	GAME_INPUT_HEAVY_KICK,
	GAME_INPUT_HEAVY_PUNCH,

	GAME_INPUT_STANCE,
	GAME_INPUT_GUARD,

	GAME_INPUT_QCF,
	GAME_INPUT_QCB,
	GAME_INPUT_HCF,
	GAME_INPUT_HCB,
	GAME_INPUT_DRAGON_FIST_FORWARD,
	GAME_INPUT_DRAGON_FIST_BACKWARD,

	NUM_GAME_INPUTS
};

const string GAME_INPUT_NAMES[NUM_GAME_INPUTS] =	
{
	"Game Input: Up",
	"Game Input: Down",
	"Game Input: Left",
	"Game Input: Right",
	
	"Game Input: North",
	"Game Input: North-West",
	"Game Input: West",
	"Game Input: South-West",
	"Game Input: South",
	"Game Input: South-East",
	"Game Input: East",
	"Game Input: North-East",
	
	"Game Input: Light Kick",
	"Game Input: Light Punch",
	"Game Input: Heavy Kick",
	"Game Input: Heavy Punch",

	"Game Input: Stance",
	"Game Input: Guard",
	
	"Game Input: Quarter Circle Forward",
	"Game Input: Quarter Circle Backward",
	"Game Input: Half Circle Forward",
	"Game Input: Half Circle Backward",
	"Game Input: Dragon Fist Forward",
	"Game Input: Dragon Fist Backward"
};

#endif