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
    ArcApp::init(Size(800, 600), "HDG Editor");

    spDefaultFont = New Font("assets/arial.ttf", 14);

    btnClose = New TextButton();
    btnClose->init(Vector2(5), "Close");

    txtTest = New Textbox();
    txtTest->init(Vector2(100));

    btnClose->addEventListener(Button::EVENT_BUTTON_CLICKED, this, &Program::btnCloseClicked);
}

void Program::term( void )
{
    btnClose->removeEventListener(Button::EVENT_BUTTON_CLICKED, this, &Program::btnCloseClicked);

    delete spDefaultFont;

    delete txtTest;
    delete btnClose;
}

void Program::update( const Event& event )
{
    ArcApp::update(event);
}

void Program::render( const Event& event )
{
    ArcApp::render(event);
}

void Program::btnCloseClicked( const Event& event )
{
    gpEventDispatcher->dispatchEvent(Event(Program::EVENT_EXIT));
}
