//#include "Player.h"
//#include "Game.h"
//
//const EventType Player::EVENT_ENEMY_LOCATION  = "eventEnemyLocation";
//const EventType Player::EVENT_CHECK_COLLISION = "eventCheckCollision";
//
//Player::Player( void )
//{
//}
//
//Player::~Player( void )
//{
//    term();
//}
//
//std::string Player::toString( void ) const
//{
//    return "Player";
//}
//
//void Player::init( PlayerIndex index, PlayerType type, Vector2 pos /*= Vector2::ZERO*/, Color color /*= Color::WHITE*/, float depth /*= 1.0f */ )
//{
//    ActiveUnit::init(nullptr, pos, Vector2::ZERO, Vector2::ZERO, Vector2::ZERO, 0.0f, color, depth);
//    IGameInputListener::init();
//
//    _playerIndex = index;
//    _playerType  = type;
//
//    getHitboxData();
//    setAnimationKeys();
//
//    switchState(PLAYER_STATE_AIR, VERT_STATE_AIR);
//
//    _gravity     = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("gravity")));
//    _ground      = 420.0f;
//    _maxSpeed    = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("maxSpeed")));
//    _jumpVelInit = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("jumpVelStart")));
//    _jumpVelMax  = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("jumpVelMax")));
//    _jumpVelLeft = _jumpVelMax;
//    _damping     = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("damping")));
//    _airDamping  = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("airDamping")));
//    _terminalVel = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("terminalVel")));
//    _movementAcc = gpDataManager->getFloat(makeVector<string>(3, _playerType, string("movement"), string("movementAcc")));
//
//    _flip = true;
//
//    _stateData = &gpDataManager->PlayerStateData[_playerType];
//}
//
//void Player::term( void )
//{
//}
//
//void Player::update( const Event& event )
//{
//    ActiveUnit::update(event);
//
//    Origin = Vector2(UnitSize.halfX(), UnitSize.Y);
//
//    if (_vertState == VERT_STATE_AIR)
//    {
//        Vel.Y -= _gravity;
//        if (Vel.Y > _terminalVel)
//            Vel.Y = _terminalVel;
//
//        if (_state == PLAYER_STATE_AIR)
//        {
//            if (abs(Vel.Y) < 3.0f)
//            {
//                setAnimation(_playerType + "-peak");
//            }
//            else
//            {
//                if (sign(Vel.Y) == 1)
//                {
//                    setAnimation(_playerType + "-descending");
//                }
//                else
//                {
//                    setAnimation(_playerType + "-ascending");
//                }
//            }
//        }
//
//        if (Pos.Y > _ground) //TODO: Replace with ground checking
//        {
//            Vel.Y = 0;
//            Pos.Y = _ground;
//            processGameInput(GAME_INPUT_LANDED);
//        }
//    }
//
//    if (abs(Vel.X) < 0.01f)
//        Vel.X = 0.0f;
//
//    if (Vel.X != 0.0f)
//    {
//        float damp;
//
//        if (_vertState == VERT_STATE_GROUND || _vertState == VERT_STATE_DUCKING)
//            damp = _damping;
//        else
//            damp = _airDamping;
//
//        Vel.X -= damp * sign(Vel.X);
//    }
//
//    dispatchEvent(Event(Player::EVENT_ENEMY_LOCATION, PointData(Pos)));
//    dispatchEvent(Event(Player::EVENT_CHECK_COLLISION, PlayerCollisionData(Pos, Origin, hurtboxes(), attackboxes())));
//}
//
//void Player::render( const Event& event )
//{
//    const RenderData* renderData = event.dataAs<RenderData>();
//
//    if (_pAnimation == nullptr)
//        return;
//
//    Sprite* currentFrame = _pAnimation->frameAt(_frame);
//
//    if (currentFrame == nullptr)
//        return;
//
//    renderData->renderTarget()->draw(Pos - Origin, currentFrame->texture(), currentFrame->SourceRect, BlendColor, Rot, Origin, _flip);
//
//    if (Game::DEBUG_SHOW_HITBOXES)
//    {
//        vector<Rect> 
//            currHurt = hurtboxes(),
//            currAtt  = attackboxes();
//
//        Rect currBox;
//
//        for (unsigned int i = 0; i < currHurt.size(); ++i)
//        {
//            currBox = currHurt[i];
//            renderData->renderTarget()->drawRect(Rect(Pos - Origin + currBox.pos(), currBox.size()), Color::GREEN);
//        }
//
//        for (unsigned int i = 0; i < currAtt.size(); ++i)
//        {
//            currBox = currAtt[i];
//            renderData->renderTarget()->drawRect(Rect(Pos - Origin + currBox.pos(), currBox.size()), Color::RED);
//        }
//    }
//}
//
//vector<Rect> Player::hurtboxes( void )
//{
//    if (!mapContainsKey(_hurtboxes, _currentAnim) || !mapContainsKey(_hurtboxes[_currentAnim], _frame))
//        return vector<Rect>();
//
//    vector<Rect> currHurtboxes = _hurtboxes[_currentAnim][_frame];
//
//    if (_flip)
//    {
//        for (unsigned int i = 0; i < currHurtboxes.size(); ++i)
//        {
//            Rect curr = currHurtboxes[i];
//            curr.X = Rect(Vector2::ZERO, UnitSize).right() - curr.right();
//            currHurtboxes[i] = curr;
//        }
//    }
//
//    return currHurtboxes;
//}
//
//vector<Rect> Player::attackboxes( void )
//{
//    if (!mapContainsKey(_attackboxes, _currentAnim) || !mapContainsKey(_attackboxes[_currentAnim], _frame))
//        return vector<Rect>();
//
//    vector<Rect> currAttackboxes = _attackboxes[_currentAnim][_frame];
//
//    if (_flip)
//    {
//        for (unsigned int i = 0; i < currAttackboxes.size(); ++i)
//        {
//            Rect curr = currAttackboxes[i];
//            curr.X = Rect(Vector2::ZERO, UnitSize).right() - curr.right();
//            currAttackboxes[i] = curr;
//        }
//    }
//    return currAttackboxes;
//}
//
//void Player::inputPressed( const Event& event )
//{
//    const GameInputData* inputData = event.dataAs<GameInputData>();
//
//    if (inputData->Index != _playerIndex)
//        return;
//
//    if (inputData->Input == GAME_INPUT_QCF || inputData->Input == GAME_INPUT_QCB || inputData->Input == GAME_INPUT_HCF || inputData->Input == GAME_INPUT_HCB || inputData->Input == GAME_INPUT_DRAGON_FIST_FORWARD || inputData->Input == GAME_INPUT_DRAGON_FIST_BACKWARD)
//        cout << GAME_INPUT_NAMES[inputData->Input] << endl;
//
//    processGameInput(inputData->Input, INPUT_TYPE_PRESSED);
//}
//
//void Player::inputReleased( const Event& event )
//{
//    const GameInputData* inputData = event.dataAs<GameInputData>();
//
//    if (inputData->Index != _playerIndex)
//        return;
//
//    processGameInput(inputData->Input, INPUT_TYPE_RELEASED);
//}
//
//void Player::inputHeld( const Event& event )
//{
//    const GameInputData* inputData = event.dataAs<GameInputData>();
//
//    if (inputData->Index != _playerIndex)
//        return;
//    
//    processGameInput(inputData->Input, INPUT_TYPE_HELD);
//
//    if (inputData->Input == GAME_INPUT_UP && _state == PLAYER_STATE_AIR)
//    {
//        if (_jumpVelLeft > 0.0f)
//        {
//            Vel.Y -= 1.0f;
//            _jumpVelLeft -= 1.0f;
//        }
//    }
//
//    if (_state == PLAYER_STATE_WALK || _vertState == VERT_STATE_AIR)
//    {
//        if (inputData->Input == GAME_INPUT_LEFT)
//        {
//            Vel.X -= _movementAcc;
//        }
//        else if (inputData->Input == GAME_INPUT_RIGHT)
//        {
//            Vel.X += _movementAcc;
//        }
//        if (abs(Vel.X) > _maxSpeed)
//            Vel.X = _maxSpeed * sign(Vel.X);
//    }
//}
//
//void Player::animationComplete( const Event& event )
//{
//    ActiveUnit::animationComplete(event);
//
//    if (_state == PLAYER_STATE_JUMPING_START)
//    {
//        Vel.Y -= _jumpVelInit;
//        _jumpVelLeft = _jumpVelMax - _jumpVelInit;
//    }
//
//    processGameInput(GAME_INPUT_ANIMATION_COMPLETE);
//}
//
//void Player::setAnimationKeys( void )
//{
//    addAnimationKey(PLAYER_STATE_IDLE,          _playerType + "-idle",               VERT_STATE_GROUND);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_DUCKING_START, _playerType + "-duck-start",         VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_DUCKING,       _playerType + "-ducking",            VERT_STATE_DUCKING);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_JUMPING_START, _playerType + "-jump-start",         VERT_STATE_GROUND);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_WALK,          _playerType + "-walk",               VERT_STATE_GROUND);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-guard",              VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-duck-guard",         VERT_STATE_DUCKING);
//    addAnimationKey(PLAYER_STATE_GUARD,         _playerType + "-air-guard",          VERT_STATE_AIR);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-glp",                VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-glk",                VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-ghp",                VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-ghk",                VERT_STATE_GROUND);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-dlp",                VERT_STATE_DUCKING);
//    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-dlk",                VERT_STATE_DUCKING);
//    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-dhp",                VERT_STATE_DUCKING);
//    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-dhk",                VERT_STATE_DUCKING);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_LIGHT_PUNCH,   _playerType + "-alp",                VERT_STATE_AIR);
//    addAnimationKey(PLAYER_STATE_LIGHT_KICK,    _playerType + "-alk",                VERT_STATE_AIR);
//    addAnimationKey(PLAYER_STATE_HEAVY_PUNCH,   _playerType + "-ahp",                VERT_STATE_AIR);
//    addAnimationKey(PLAYER_STATE_HEAVY_KICK,    _playerType + "-ahk",                VERT_STATE_AIR);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_GRAB,          _playerType + "-grab",               VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_GRAB_MISS,     _playerType + "-grab-miss",          VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_LANDING,       _playerType + "-landing",            VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_KNOCKDOWN,     _playerType + "-knockdown",          VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_RECOVERY,      _playerType + "-recovery",           VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_JUGGLE,        _playerType + "-juggle",             VERT_STATE_AIR);
//                                                                                     
//    addAnimationKey(PLAYER_STATE_HIT_STUN,      _playerType + "-hit-stun",           VERT_STATE_GROUND);
//    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-guard-stun",         VERT_STATE_GROUND);
//
//    addAnimationKey(PLAYER_STATE_HIT_STUN,      _playerType + "-ducking-hit-stun",   VERT_STATE_DUCKING);
//    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-ducking-guard-stun", VERT_STATE_DUCKING);
//
//    addAnimationKey(PLAYER_STATE_GUARD_STUN,    _playerType + "-air-guard-stun",     VERT_STATE_AIR);
//}
//
//void Player::addAnimationKey( PlayerState state, ItemKey key, VerticalState vertState /*= VERT_STATE_ANY */ )
//{
//    _animKeys.insert(pair<PlayerStatePair, ItemKey>(PlayerStatePair(vertState, state), key));
//}
//
//void Player::switchState( PlayerState state /*= INVALID_PLAYER_STATE*/, VerticalState vertState /*= INVALID_VERTICAL_STATE */ )
//{
//    if (_state == state && _vertState == vertState)
//        return;
//
//    if (_state != INVALID_PLAYER_STATE)
//        _state = state;
//
//    if (_vertState != INVALID_VERTICAL_STATE)
//        _vertState = vertState;
//
//    PlayerStatePair statePair(vertState, state);
//
//    if (mapContainsKey(_animKeys, statePair))
//    {
//        if (!gpDataManager->pAnimations->contains(_animKeys[statePair]))
//            return;
//
//        setAnimation(_animKeys[statePair]);
//    }
//}
//
//void Player::processGameInput( GameInput input, InputType type /*= INPUT_TYPE_OTHER*/ )
//{
//    pair<GameInput, InputType> typePair(input, type);
//
//    if (mapContainsKey(*_stateData, typePair))
//    {
//        if (mapContainsKey((*_stateData)[typePair], _vertState))
//        {
//            PlayerStateChangeList list = (*_stateData)[typePair][_vertState];
//
//            for (unsigned int i = 0; i < list.size(); ++i)
//            {
//                if (list[i].OldState == _state)
//                {
//                    switchState(list[i].NewState, list[i].NewVertState);
//                }
//            }
//        }
//    }
//}
//
//void Player::updateEnemyLocation( const Event& event )
//{
//    const PointData* data = event.dataAs<PointData>();
//
//    if (Pos.X > data->X)
//    {
//        _flip = true;
//    }
//    else
//    {
//        _flip = false;
//    }
//}
//
//void Player::checkCollision( const Event& event )
//{
//    const PlayerCollisionData* data = event.dataAs<PlayerCollisionData>();
//
//    vector<Rect>
//        currHurt = hurtboxes(),
//        currAtt  = attackboxes();
//
//    bool 
//        wasHit  = false,
//        hitThem = false;
//
//    for (unsigned int hurtInd = 0; hurtInd < currHurt.size(); ++hurtInd)
//    {
//        Rect hurtCheck = currHurt[hurtInd] + Rect(Pos + Origin, Vector2::ZERO);
//
//        for (unsigned int attInd = 0; attInd < data->Attackboxes.size(); ++attInd)
//        {
//            Rect attCheck = data->Attackboxes[attInd] + Rect(data->Pos + data->Origin, Vector2::ZERO);
//
//            if (hurtCheck.collides(attCheck))
//            {
//                collided();
//            }
//        }
//    }
//}
//
//void Player::getHitboxData( void )
//{
//    ConfigLevel* hitboxes = gpDataManager->getLevel(makeVector<string>(2, _playerType, string("hitbox")));
//    vector<string> hitboxAnimKeys = hitboxes->getLevelKeys();
//
//    for (unsigned int animInd = 0; animInd < hitboxAnimKeys.size(); ++animInd)
//    {
//        string currAnim = hitboxAnimKeys[animInd];
//
//        _hurtboxes.insert(  pair<string, map<int, vector<Rect>>>(currAnim, map<int, vector<Rect>>()));
//        _attackboxes.insert(pair<string, map<int, vector<Rect>>>(currAnim, map<int, vector<Rect>>()));
//
//        ConfigLevel* hitboxAnims = hitboxes->getLevel(currAnim);
//        vector<string> frameKeys = hitboxAnims->getLevelKeys();
//
//        for (unsigned int frameInd = 0; frameInd < frameKeys.size(); ++frameInd)
//        {
//            string frameKey = frameKeys[frameInd];
//            int frame = parseInt(frameKey);
//
//            ConfigLevel* frameData = hitboxAnims->getLevel(frameKey);
//
//            _hurtboxes[currAnim].insert(  pair<int, vector<Rect>>(frame, gpDataManager->getRectList(makeVector<string>(5, _playerType, string("hitbox"), currAnim, frameKey, string("Hurtboxes")))));
//            _attackboxes[currAnim].insert(pair<int, vector<Rect>>(frame, gpDataManager->getRectList(makeVector<string>(5, _playerType, string("hitbox"), currAnim, frameKey, string("Attackboxes")))));
//        }
//    }
//}
//
//void Player::setAnimation( ItemKey key )
//{
//    _currentAnim = key;
//
//    setAnimation(gpDataManager->pAnimations->get(key));
//}
//
//void Player::collided( void )
//{
//    processGameInput(GAME_INPUT_HIT);
//}
//