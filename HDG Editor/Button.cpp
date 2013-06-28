#include "Button.h"
#include "Program.h"
#include "MouseSource.h"

const EventType Button::EVENT_BUTTON_PRESSED     = "buttonPressed";
const EventType Button::EVENT_BUTTON_RELEASED    = "buttonReleased";
const EventType Button::EVENT_BUTTON_CLICKED     = "buttonClicked";
const EventType Button::EVENT_BUTTON_HOVER_ENTER = "buttonHoverEnter";
const EventType Button::EVENT_BUTTON_HOVER_LEAVE = "buttonHoverLeave";

Button::Button(void)
{
}

Button::~Button(void)
{
    term();
}

std::string Button::toString( void ) const
{
    return "Button";
}

void Button::init( Vector2 pos /*= Vector2::ZERO*/, Vector2 padding /*= Vector2::ZERO*/ )
{
    Component::init(pos, padding);

    _held  = false;

    Padding = Vector2(5.0f);
}

void Button::term( void )
{
}

void Button::mouseMoved( const Event& event )
{
    Component::mouseMoved(event);

    const MouseData* data = event.dataAs<MouseData>();

    if (!bounds().containsPoint(data->Pos))
    {
        _held = false;
    }
}

void Button::mousePressed( const Event& event )
{
    Component::mousePressed(event);

    const MouseData* data = event.dataAs<MouseData>();
    
    switch (data->Button)
    {
    case MouseButton::MOUSE_BUTTON_LEFT:
    
        if (_hover)
        {
            dispatchEvent(Event(EVENT_BUTTON_PRESSED));
            _held = true;
        }
    
        break;
    }
}

void Button::mouseReleased( const Event& event )
{
    Component::mouseReleased(event);

    const MouseData* data = event.dataAs<MouseData>();
    
    switch (data->Button)
    {
    case MouseButton::MOUSE_BUTTON_LEFT:
    
        if (_hover)
        {
            dispatchEvent(Event(EVENT_BUTTON_RELEASED));
            if (_held)
            {
                dispatchEvent(Event(EVENT_BUTTON_CLICKED));
                _held = false;
            }
        }
    
        break;
    }
}

void Button::hoverEnter( void )
{
    Component::hoverEnter();

    dispatchEvent(Event(Button::EVENT_BUTTON_HOVER_ENTER));
}

void Button::hoverLeave( void )
{
    Component::hoverLeave();

    dispatchEvent(Event(Button::EVENT_BUTTON_HOVER_LEAVE));
}
