#include "Program.h"

Font * Program::spDefaultFont = nullptr;

Program::Program(void)
{
}

Program::~Program(void)
{
    term();
}

std::string Program::toString( void ) const
{
    return "Program";
}

void Program::init( void )
{
    ArcApp::init(Size(850, 650), "HDG Editor");
    IMouseListener::init();
    IKeyboardListener::init();

    _pGraphicsSystem->setClearColor(Color(180, 180, 180));

    gpDataManager = New DataManager();
    gpDataManager->init();

    spDefaultFont = New Font("assets/arial.ttf", 14);

    _currCharacter = "";
    _currAnim      = "";
    _currFrame     = -1;

    _drawingAttack = false;
    _drawingHurt   = false;

    _currHurtboxes   = map<int, vector<Rect>>();
    _currAttackboxes = map<int, vector<Rect>>();
    _rectPoints      = vector<Vector2>();

    _mousePos  = Vector2::ZERO;
    _workspace = Rect(290.0f, 90.0f, 550.0f, 550.0f);
    _frameRect = Rect::ZERO;

    _characters = makeVector(4, string("toast"), string("wolf"), string("ghost"), string("curl"));

    _pBtnFrameLeft      = New TextButton();
    _pBtnFrameRight     = New TextButton();
    _pBtnToolDrawAttack = New TextButton();
    _pBtnToolDrawHurt   = New TextButton();
    _pBtnClearAttack    = New TextButton();
    _pBtnClearHurt      = New TextButton();
    _pBtnSaveAnimation  = New TextButton();

    _pBtnFrameLeft->init     (Vector2(300.0f, 10.0f),  "<");
    _pBtnFrameRight->init    (Vector2(350.0f, 10.0f),  ">");
    _pBtnToolDrawAttack->init(Vector2(20.0f,  100.0f), "Add Attackbox");
    _pBtnToolDrawHurt->init  (Vector2(20.0f,  130.0f), "Add Hurtbox");
    _pBtnClearAttack->init   (Vector2(20.0f,  170.0f), "Clear Attackboxes");
    _pBtnClearHurt->init     (Vector2(20.0f,  200.0f), "Clear Hurtboxes");
    _pBtnSaveAnimation->init (Vector2(20.0f,  250.0f), "Save Animation");

    _pLblCurrentFrame = New Label();
    _pLblCurrentFrame->init(Vector2(325.0f, 16.0f), "0/0");

    _pDrpCharacter = New Dropdown();
    _pDrpCharacter->init(Vector2(10.0f), _characters);

    _pDrpAnimation = New Dropdown();
    _pDrpAnimation->init(Vector2(100.0f, 10.0f));
    _pDrpAnimation->MaxRows = 15;

    _pDrpCharacter->addEventListener     (Dropdown::EVENT_SELECTED_INDEX_CHANGED, this, &Program::drpCharacterChanged);
    _pDrpAnimation->addEventListener     (Dropdown::EVENT_SELECTED_INDEX_CHANGED, this, &Program::drpAnimationChanged);
    _pBtnFrameLeft->addEventListener     (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnFrameLeftClicked);
    _pBtnFrameRight->addEventListener    (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnFrameRightClicked);
    _pBtnToolDrawAttack->addEventListener(Button::EVENT_BUTTON_CLICKED,           this, &Program::btnToolDrawAttackClicked);
    _pBtnToolDrawHurt->addEventListener  (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnToolDrawHurtClicked);
    _pBtnClearAttack->addEventListener   (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnClearAttackClicked);
    _pBtnClearHurt->addEventListener     (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnClearHurtClicked);
    _pBtnSaveAnimation->addEventListener (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnSaveAnimationClicked);
}

void Program::term( void )
{
    _pBtnSaveAnimation->removeEventListener (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnSaveAnimationClicked);
    _pBtnClearHurt->removeEventListener     (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnClearHurtClicked);
    _pBtnClearAttack->removeEventListener   (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnClearAttackClicked);
    _pBtnToolDrawHurt->removeEventListener  (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnToolDrawHurtClicked);
    _pBtnToolDrawAttack->removeEventListener(Button::EVENT_BUTTON_CLICKED,           this, &Program::btnToolDrawAttackClicked);
    _pBtnFrameRight->removeEventListener    (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnFrameRightClicked);
    _pBtnFrameLeft->removeEventListener     (Button::EVENT_BUTTON_CLICKED,           this, &Program::btnFrameLeftClicked);
    _pDrpAnimation->removeEventListener     (Dropdown::EVENT_SELECTED_INDEX_CHANGED, this, &Program::drpAnimationChanged);
    _pDrpCharacter->removeEventListener     (Dropdown::EVENT_SELECTED_INDEX_CHANGED, this, &Program::drpCharacterChanged);

    delete _pDrpAnimation;
    delete _pDrpCharacter;

    delete _pLblCurrentFrame;

    delete _pBtnSaveAnimation;
    delete _pBtnClearHurt;
    delete _pBtnClearAttack;
    delete _pBtnToolDrawHurt;
    delete _pBtnToolDrawAttack;
    delete _pBtnFrameRight;
    delete _pBtnFrameLeft;

    delete spDefaultFont;
    delete gpDataManager;
}

void Program::update( const Event& event )
{
    ArcApp::update(event);
}

void Program::render( const Event& event )
{
    ArcApp::render(event);

    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    renderTarget->drawRect(_workspace, Color::BLACK);
    renderTarget->fillRect(_workspace, Color::WHITE);

    if (_currAnim != "" && _currFrame != -1)
    {
        Sprite *frame = currentAnimation()->frameAt(_currFrame);
        _frameRect = Rect(_workspace.pos(), frame->SourceRect.size());

        renderTarget->draw(_workspace.pos(), frame->texture(), frame->SourceRect);
        renderTarget->drawRect(Rect(_workspace.pos(), frame->SourceRect.size()), Color::BLACK);

        if ((_drawingHurt || _drawingAttack) && _rectPoints.size() == 1 && _frameRect.containsPoint(_mousePos))
        {
            renderTarget->drawRect(Rect(_workspace.pos() + _rectPoints[0], (_mousePos - _workspace.pos()) - _rectPoints[0]), Color::GREEN);
        }

        for (unsigned int i = 0; i < _currHurtboxes[_currFrame].size(); ++i)
        {
            renderTarget->drawRect(Rect(_workspace.pos() + _currHurtboxes[_currFrame][i].pos(), _currHurtboxes[_currFrame][i].size()), Color::BLUE);
        }

        for (unsigned int i = 0; i < _currAttackboxes[_currFrame].size(); ++i)
        {
            renderTarget->drawRect(Rect(_workspace.pos() + _currAttackboxes[_currFrame][i].pos(), _currAttackboxes[_currFrame][i].size()), Color::RED);
        }
    }
}

void Program::drpCharacterChanged( const Event& event )
{
    const DropdownChangedData* data = event.dataAs<DropdownChangedData>();

    if (data->Index == -1)
        return;

    _currCharacter = data->Item;
    _currAnim      = "";
    _currFrame     = -1;

    _pDrpAnimation->Index = -1;
    _pDrpAnimation->Items = gpDataManager->getStringList(makeVector(3, data->Item, string("assets"), string("animations")));
}

void Program::drpAnimationChanged( const Event& event )
{
    const DropdownChangedData* data = event.dataAs<DropdownChangedData>();

    _currAnim  = data->Item;
    _currFrame = 0;

    updateCurrentFrameLabel();

    _currHurtboxes.clear();
    _currAttackboxes.clear();

    stringstream ss;
    for (int i = 0; i < currentAnimation()->length(); ++i)
    {
        ss.str("");
        ss << i;

        _currHurtboxes.insert(  pair<int, vector<Rect>>(i, gpDataManager->getRectList(makeVector(5, _currCharacter, string("hitbox"), _currAnim, ss.str(), string("Hurtboxes")))));
        _currAttackboxes.insert(pair<int, vector<Rect>>(i, gpDataManager->getRectList(makeVector(5, _currCharacter, string("hitbox"), _currAnim, ss.str(), string("Attackboxes")))));
    }
}

void Program::btnFrameLeftClicked( const Event& event )
{
    prevFrame();
}

void Program::btnFrameRightClicked( const Event& event )
{
    nextFrame();
}

void Program::btnClearHurtClicked( const Event& event )
{
    clearHurtboxes();
}

void Program::btnClearAttackClicked( const Event& event )
{
    clearAttackboxes();
}

void Program::btnToolDrawHurtClicked( const Event& event )
{
    toggleDrawHurtbox();
}

void Program::btnToolDrawAttackClicked( const Event& event )
{
    toggleDrawAttackbox();
}

void Program::btnSaveAnimationClicked( const Event& event )
{
    saveHitboxData();
}

void Program::updateCurrentFrameLabel( void )
{
    if (_currAnim == "")
    {
        _pLblCurrentFrame->setText("0/0");
        return;
    }

    stringstream ss;
    ss << (_currFrame + 1) << "/" << currentAnimation()->length();

    _pLblCurrentFrame->setText(ss.str());
}

Animation* Program::currentAnimation( void )
{
    return gpDataManager->pAnimations->get(_currAnim);
}

void Program::mouseReleased( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    addHitboxPoint(data->Pos);
}

void Program::mouseMoved( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    _mousePos = data->Pos;
}

void Program::addHitboxPoint( Vector2 point )
{
    if (_frameRect.containsPoint(point))
    {
        _rectPoints.push_back(point - _workspace.pos());

        if (_rectPoints.size() == 2)
        {
            Rect rect = Rect(_rectPoints[0], (_mousePos - _workspace.pos()) - _rectPoints[0]);

            if (_drawingHurt)
            {
                _currHurtboxes[_currFrame].push_back(rect);
                _pBtnToolDrawHurt->setText("Add Hurtbox");
            }
            else if (_drawingAttack)
            {
                _currAttackboxes[_currFrame].push_back(rect);
                _pBtnToolDrawAttack->setText("Add Attackbox");
            }

            _drawingHurt   = false;
            _drawingAttack = false;

            _rectPoints.clear();
        }
    }
}

void Program::nextFrame( void )
{
    if (_currAnim == "")
        return;

    _currFrame = (_currFrame + 1) % currentAnimation()->length();

    updateCurrentFrameLabel();
}

void Program::prevFrame( void )
{
    if (_currAnim == "")
        return;

    _currFrame = (_currFrame - 1);
    if (_currFrame < 0)
        _currFrame = currentAnimation()->length() - 1;

    updateCurrentFrameLabel();
}

void Program::toggleDrawHurtbox( void )
{
    if (_currAnim == "")
        return;

    _drawingHurt = !_drawingHurt;

    if (_drawingHurt)
    {
        _pBtnToolDrawHurt->setText("Cancel");
    }
    else
    {
        _pBtnToolDrawHurt->setText("Add Hurtbox");
        _rectPoints.clear();
    }
}

void Program::toggleDrawAttackbox( void )
{
    if (_currAnim == "")
        return;

    _drawingAttack = !_drawingAttack;

    if (_drawingAttack)
    {
        _pBtnToolDrawAttack->setText("Cancel");
    }
    else
    {
        _pBtnToolDrawAttack->setText("Add Attackbox");
        _rectPoints.clear();
    }
}

void Program::clearHurtboxes( void )
{
    if (_currAnim == "")
        return;

    _currHurtboxes[_currFrame].clear();
}

void Program::clearAttackboxes( void )
{
    if (_currAnim == "")
        return;

    _currAttackboxes[_currFrame].clear();
}

void Program::saveHitboxData( void )
{
    if (_currAnim == "")
        return;

    ofstream file(gpDataManager->BaseDir + "assets/config/" + _currCharacter + "/hitbox.cfg");

    file << "!Start hitbox\n\n";

    ConfigLevel* hitboxLevel = gpDataManager->getLevel(makeVector(2, _currCharacter, string("hitbox")));

    vector<string> animKeys = hitboxLevel->getLevelKeys();

    if (!vectorContains(animKeys, _currAnim))
        animKeys.push_back(_currAnim);

    for (unsigned int animInd = 0; animInd < animKeys.size(); ++animInd)
    {
        ConfigLevel* animLevel = hitboxLevel->getLevel(animKeys[animInd]);

        file << "!Start " << animKeys[animInd] << "\n\n";

        if (animKeys[animInd] == _currAnim)
        {
            map<int, vector<Rect>>::iterator it;

            stringstream ss;
            for (it = _currHurtboxes.begin(); it != _currHurtboxes.end(); ++it)
            {
                ss.str("");
                ss << it->first;
                string frameKey = ss.str();
                ConfigLevel* frameLevel = animLevel->getLevel(frameKey);
                vector<Rect> list;
                unsigned int rectInd;

                file << "!Start " << frameKey << "\n\n";

                file << "!StartList Hurtboxes\n";

                list = _currHurtboxes[it->first];
                for (rectInd = 0; rectInd < list.size(); ++rectInd)
                {
                    Rect rect = list[rectInd];

                    file << rect.X << " " << rect.Y << " " << rect.Width << " " << rect.Height << "\n";
                }

                file << "!EndList Hurtboxes\n\n";

                file << "!StartList Attackboxes\n";

                list = _currAttackboxes[it->first];
                for (rectInd = 0; rectInd < list.size(); ++rectInd)
                {
                    Rect rect = list[rectInd];

                    file << rect.X << " " << rect.Y << " " << rect.Width << " " << rect.Height << "\n";
                }

                file << "!EndList Attackboxes\n\n";

                file << "!End " << frameKey << "\n\n";
            }
        }
        else
        {
            vector<string> frameKeys = animLevel->getLevelKeys();
            for (unsigned int frameInd = 0; frameInd < frameKeys.size(); ++frameInd)
            {
                ConfigLevel* frameLevel = animLevel->getLevel(frameKeys[frameInd]);
                vector<string> list;
                unsigned int rectInd;

                file << "!Start " << frameKeys[frameInd] << "\n\n";

                file << "!StartList Hurtboxes\n";

                list = *frameLevel->getList("Hurtboxes");
                for (rectInd = 0; rectInd < list.size(); ++rectInd)
                {
                    file << list[rectInd] << "\n";
                }

                file << "!EndList Hurtboxes\n\n";

                file << "!StartList Attackboxes\n";

                list = *frameLevel->getList("Attackboxes");
                for (unsigned int rectInd = 0; rectInd < list.size(); ++rectInd)
                {
                    file << list[rectInd] << "\n";
                }

                file << "!EndList Attackboxes\n\n";

                file << "!End " << frameKeys[frameInd] << "\n\n";
            }
        }

        file << "!End " << animKeys[animInd] << "\n\n";
    }

    file << "!End hitbox\n";

    file.close();
}

void Program::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_LEFT:

        prevFrame();

        break;
    case KEY_RIGHT:

        nextFrame();

        break;
    case KEY_A:

        toggleDrawAttackbox();

        break;
    case KEY_H:

        toggleDrawHurtbox();

        break;
    case KEY_S:

        clearAttackboxes();

        break;
    case KEY_J:

        clearHurtboxes();

        break;
    case KEY_ESCAPE:

        if (_drawingAttack)
        {
            toggleDrawAttackbox();
        }
        else if (_drawingHurt)
        {
            toggleDrawHurtbox();
        }

        break;
    }
}