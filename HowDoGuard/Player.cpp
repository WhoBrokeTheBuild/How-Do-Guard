#include "Player.h"

Player::Player( void )
{
}

Player::~Player( void )
{
	term();
}

std::string Player::toString( void ) const
{
	return "Player";
}

void Player::init( Vector2 pos /*= Vector2::ZERO*/, Color color /*= Color::WHITE*/, float depth /*= 1.0f */ )
{
	ActiveUnit::init(nullptr, pos, Vector2::ZERO, Vector2::ZERO, Vector2::ZERO, 0.0f, color, depth);

	setAnimationKeys();

	switchState(PLAYER_STATE_AIR, VERT_STATE_AIR);

	_gravity = -0.8f;
	_ground = 420.0f;
	_jumpVel = 15.0f;

	_stateData = &gpDataManager->PlayerStateData["toast"];
}

void Player::term( void )
{
	ActiveUnit::term();
}

void Player::update( const Event& event )
{
	ActiveUnit::update(event);

	//cout << PLAYER_STATE_NAMES[_state] << endl;

	if (_vertState == VERT_STATE_AIR)
	{
		Vel.Y -= _gravity;

		if (_state == PLAYER_STATE_AIR)
		{
			if (sign(Vel.Y) == 1)
			{
				setAnimation(gpDataManager->pAnimations->get("toast-descending"));
			}
			else
			{
				setAnimation(gpDataManager->pAnimations->get("toast-ascending"));
			}
		}

		if (Pos.Y + 255 > _ground)
		{
			Vel.X = Vel.Y = 0;
			Pos.Y = _ground - 255;
			checkStateData(GAME_INPUT_LANDED);
		}
	}
}

void Player::inputPressed( const Event& event )
{
	ActiveUnit::inputPressed(event);

	const InputData* inputData = event.dataAs<InputData>();

	checkStateData(inputData->Input, GAME_INPUT_TYPE_PRESSED);
}

void Player::inputReleased( const Event& event )
{
	ActiveUnit::inputReleased(event);

	const InputData* inputData = event.dataAs<InputData>();

	checkStateData(inputData->Input, GAME_INPUT_TYPE_RELEASED);
}

void Player::inputHeld( const Event& event )
{
	ActiveUnit::inputHeld(event);

	const InputData* inputData = event.dataAs<InputData>();
	
	checkStateData(inputData->Input, GAME_INPUT_TYPE_HELD);
}

void Player::animationComplete( const Event& event )
{
	ActiveUnit::animationComplete(event);

	checkStateData(GAME_INPUT_ANIMATION_COMPLETE);
}

void Player::setAnimationKeys( void )
{
	addAnimationKey(PLAYER_STATE_IDLE,			"toast-idle",				VERT_STATE_GROUND);

	addAnimationKey(PLAYER_STATE_DUCKING_START,	"toast-duck-start",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_DUCKING,		"toast-ducking",			VERT_STATE_DUCKING);

	addAnimationKey(PLAYER_STATE_JUMPING_START,	"toast-jump-start",			VERT_STATE_GROUND);

	addAnimationKey(PLAYER_STATE_WALK,			"toast-walk",				VERT_STATE_GROUND);

	addAnimationKey(PLAYER_STATE_GUARD,			"toast-guard",				VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_GUARD,			"toast-ducking-guard",		VERT_STATE_DUCKING);
	addAnimationKey(PLAYER_STATE_GUARD,			"toast-air-guard",			VERT_STATE_AIR);

	addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,	"toast-glp",				VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_LIGHT_KICK,	"toast-glk",				VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,	"toast-ghp",				VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_HEAVY_KICK,	"toast-ghk",				VERT_STATE_GROUND);

	addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,	"toast-dlp",				VERT_STATE_DUCKING);
	addAnimationKey(PLAYER_STATE_LIGHT_KICK,	"toast-dlk",				VERT_STATE_DUCKING);
	addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,	"toast-dhp",				VERT_STATE_DUCKING);
	addAnimationKey(PLAYER_STATE_HEAVY_KICK,	"toast-dhk",				VERT_STATE_DUCKING);

	addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,	"toast-alp",				VERT_STATE_AIR);
	addAnimationKey(PLAYER_STATE_LIGHT_KICK,	"toast-alk",				VERT_STATE_AIR);
	addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,	"toast-ahp",				VERT_STATE_AIR);
	addAnimationKey(PLAYER_STATE_HEAVY_KICK,	"toast-ahk",				VERT_STATE_AIR);

	addAnimationKey(PLAYER_STATE_GRAB,			"toast-grab",				VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_GRAB_MISS,		"toast-grab-miss",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_LANDING,		"toast-landing",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_KNOCKDOWN,		"toast-knockdown",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_RECOVERY,		"toast-recovery",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_JUGGLE,		"toast-juggle",				VERT_STATE_AIR);

	addAnimationKey(PLAYER_STATE_HIT_STUN,		"toast-hit-stun",			VERT_STATE_GROUND);
	addAnimationKey(PLAYER_STATE_GUARD_STUN,	"toast-guard-stun",			VERT_STATE_GROUND);

	addAnimationKey(PLAYER_STATE_HIT_STUN,		"toast-ducking-hit-stun",	VERT_STATE_DUCKING);
	addAnimationKey(PLAYER_STATE_GUARD_STUN,	"toast-ducking-guard-stun",	VERT_STATE_DUCKING);

	addAnimationKey(PLAYER_STATE_GUARD_STUN,	"toast-air-guard-stun",		VERT_STATE_AIR);
}

void Player::addAnimationKey( PlayerState state, ItemKey key, VerticalState vertState /*= VERT_STATE_ANY */ )
{
	_animKeys.insert(pair<pair<VerticalState, PlayerState>, ItemKey>(pair<VerticalState, PlayerState>(vertState, state), key));
}

void Player::switchState( PlayerState state /*= INVALID_PLAYER_STATE*/, VerticalState vertState /*= INVALID_VERTICAL_STATE */ )
{
	if (_state == state && _vertState == vertState)
		return;

	if (_state == PLAYER_STATE_JUMPING_START && state == PLAYER_STATE_AIR)
	{
		Vel.Y -= _jumpVel;
	}

	if (_state != INVALID_PLAYER_STATE)
		_state = state;

	if (_vertState != INVALID_VERTICAL_STATE)
		_vertState = vertState;

	if (_state == PLAYER_STATE_AIR && _vertState == VERT_STATE_AIR)
		return;

	pair<VerticalState, PlayerState> statePair(vertState, state);

	if (mapContainsKey(_animKeys, statePair))
	{
		if (!gpDataManager->pAnimations->contains(_animKeys[statePair]))
			return;

		setAnimation(gpDataManager->pAnimations->get(_animKeys[statePair]));
	}
}

void Player::checkStateData( GameInput input, GameInputType type /*= GAME_INPUT_TYPE_OTHER*/ )
{
	pair<GameInput, GameInputType> typePair(input, type);

	if (mapContainsKey(*_stateData, typePair))
	{
		if (mapContainsKey((*_stateData)[typePair], _vertState))
		{
			PlayerStateChangeList list = (*_stateData)[typePair][_vertState];

			for (unsigned int i = 0; i < list.size(); ++i)
			{
				if (list[i].OldState == _state)
				{
					switchState(list[i].NewState, list[i].NewVertState);
				}
			}
		}
	}
}
