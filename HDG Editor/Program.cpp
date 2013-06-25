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
    Game::init();

    _pGraphicsSystem->setWindowSize(Size(800, 600));

    spDefaultFont = New Font("assets/arial.ttf", 14);

    button = New Button();
    button->init(Vector2(100), "Test Button");

    button->addEventListener(Button::EVENT_BUTTON_HOVER_ENTER, this, &Program::testEnter);
    button->addEventListener(Button::EVENT_BUTTON_HOVER_LEAVE, this, &Program::testLeave);
    button->addEventListener(Button::EVENT_BUTTON_PRESSED,     this, &Program::testPress);
    button->addEventListener(Button::EVENT_BUTTON_RELEASED,    this, &Program::testRelease);
    button->addEventListener(Button::EVENT_BUTTON_CLICKED,     this, &Program::testClick);
}

void Program::term( void )
{
    button->removeEventListener(Button::EVENT_BUTTON_HOVER_ENTER, this, &Program::testEnter);
    button->removeEventListener(Button::EVENT_BUTTON_HOVER_LEAVE, this, &Program::testLeave);
    button->removeEventListener(Button::EVENT_BUTTON_PRESSED,     this, &Program::testPress);
    button->removeEventListener(Button::EVENT_BUTTON_RELEASED,    this, &Program::testRelease);
    button->removeEventListener(Button::EVENT_BUTTON_CLICKED,     this, &Program::testClick);

    delete spDefaultFont;

    delete button;
}

void Program::update( const Event& event )
{
    Game::update(event);
}

void Program::render( const Event& event )
{
    Game::render(event);
}

void Program::testEnter( const Event& event )
{
    _pGraphicsSystem->setWindowTitle("herp");
}

void Program::testLeave( const Event& event )
{
    _pGraphicsSystem->setWindowTitle("derp");
}

void Program::testPress( const Event& event )
{
}

void Program::testRelease( const Event& event )
{
}

void Program::testClick( const Event& event )
{
    _pGraphicsSystem->setFullscreen(!_pGraphicsSystem->fullscreen());
}
