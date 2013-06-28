#include "Component.h"
#include "Program.h"

Component::Component(void)
{
}

Component::~Component(void)
{
    term();
}

std::string Component::toString( void ) const
{
    return "Component";
}

void Component::init( Vector2 pos /*= Vector2::ZERO*/, Vector2 padding /*= Vector2::ZERO*/ )
{
    IMouseListener::init();

    _hover = false;

    Pos     = pos;
    Padding = padding;

    gpEventDispatcher->addEventListener(Program::EVENT_FRAME,  this, &Component::update);
    gpEventDispatcher->addEventListener(Program::EVENT_RENDER, this, &Component::render);
}

void Component::term( void )
{
    gpEventDispatcher->removeEventListener(Program::EVENT_RENDER, this, &Component::render);
    gpEventDispatcher->removeEventListener(Program::EVENT_FRAME,  this, &Component::update);
}

void Component::mousePressed( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    switch (data->Button)
    {
    case MouseButton::MOUSE_BUTTON_LEFT:

        if (_hover)
        {
            clickedOn();
        }
        else
        {
            clickedOff();
        }

        break;
    }
}

void Component::mouseMoved( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    if (bounds().containsPoint(data->Pos))
    {
        if (!_hover)
        {
            hoverEnter();
        }
    }
    else
    {
        if (_hover)
        {
            hoverLeave();
        }
    }
}

void Component::hoverEnter( void )
{
    _hover = true;
}

void Component::hoverLeave( void )
{
    _hover = false;
}

void Component::clickedOn( void )
{
    Focus = true;
}

void Component::clickedOff( void )
{
    Focus = false;
}
