//#pragma once
//
//#ifndef __PLAYER_H__
//#define __PLAYER_H__
//
//#include "Common.h"
//#include <ActiveUnit.h>
//#include <EventDispatcher.h>
//
//#include <InputType.h>
//
//#include "EventData.h"
//
//#include "DataManager.h"
//
//#include "VerticalState.h"
//#include "PlayerState.h"
//#include "PlayerStateChange.h"
//
//#include "GameInput.h"
//#include "IGameInputListener.h"
//
//typedef Map<VerticalState, PlayerState> PlayerStateMap;
//typedef string PlayerType;
//
//class PlayerCollisionData
//    : public EventData
//{
//public:
//
//    vector<Rect>
//        Hurtboxes,
//        Attackboxes;
//
//    Vector2
//        Pos,
//        Origin;
//
//    PlayerCollisionData(Vector2 pos, Vector2 origin, vector<Rect> hurtboxes, vector<Rect> attacboxes)
//    {
//        Pos         = pos;
//        Origin      = origin;
//        Hurtboxes   = hurtboxes;
//        Attackboxes = attacboxes;
//    }
//
//    virtual string toString( void ) const { return "Player Collision Data"; }
//
//    virtual EventData* clone( void ) const { return New PlayerCollisionData(Pos, Origin, Hurtboxes, Attackboxes); }
//
//};
//
//class Player :
//    public ActiveUnit,
//    public IGameInputListener
//{
//protected:
//
//    map<PlayerStateMap::Pair, ItemKey>
//        _animKeys;
//
//    map<string, map<int, vector<Rect>>>
//        _hurtboxes,
//        _attackboxes;
//
//    PlayerStateMap
//        *_stateData;
//
//    PlayerState
//        _state;
//
//    VerticalState
//        _vertState;
//
//    PlayerIndex 
//        _playerIndex;
//
//    PlayerType
//        _playerType;
//
//    ItemKey
//        _currentAnim;
//
//    float
//        _gravity,
//        _ground,
//        _maxSpeed,
//        _jumpVelInit,
//        _jumpVelMax,
//        _jumpVelLeft,
//        _damping,
//        _terminalVel,
//        _airDamping,
//        _movementAcc;
//
//    bool
//        _flip;
//
//    virtual void setAnimationKeys( void );
//    virtual void addAnimationKey( PlayerState state, ItemKey key, VerticalState vertState = VERT_STATE_ANY );
//
//    virtual void processGameInput( GameInput input, InputType type = INPUT_TYPE_OTHER );
//    virtual void getHitboxData( void );
//
//public:
//
//    static const EventType 
//        EVENT_ENEMY_LOCATION,
//        EVENT_CHECK_COLLISION;
//
//    Player( void );
//    virtual ~Player( void );
//
//    virtual string toString( void ) const;
//
//    virtual void init( PlayerIndex index, PlayerType playerType, Vector2 pos = Vector2::ZERO, Color color = Color::WHITE, float depth = 1.0f );
//    virtual void term( void );
//
//    virtual void update( const Event& event );
//    virtual void render( const Event& event );
//
//    virtual vector<Rect> hurtboxes  ( void );
//    virtual vector<Rect> attackboxes( void );
//
//    virtual void inputPressed ( const Event& event );
//    virtual void inputReleased( const Event& event );
//    virtual void inputHeld    ( const Event& event );
//
//    virtual void switchState( PlayerState state = INVALID_PLAYER_STATE, VerticalState vertState = INVALID_VERTICAL_STATE );
//
//    virtual void animationComplete  ( const Event& event );
//    virtual void updateEnemyLocation( const Event& event );
//    virtual void checkCollision     ( const Event& event );
//
//    virtual void setAnimation( Animation *pAnimation, bool useDefaults = true ) { ActiveUnit::setAnimation(pAnimation, useDefaults); }
//    virtual void setAnimation( ItemKey key );
//
//    virtual void collided( void );
//
//};
//
//#endif