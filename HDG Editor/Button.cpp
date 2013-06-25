#include "Button.h"
#include "Program.h"

const EventType Button::EVENT_BUTTON_PRESSED     = "buttonPressed";
const EventType Button::EVENT_BUTTON_RELEASED    = "buttonReleased";
const EventType Button::EVENT_BUTTON_CLICKED     = "buttonClicked";
const EventType Button::EVENT_BUTTON_HOVER_ENTER = "buttonHoverEnter";
const EventType Button::EVENT_BUTTON_HOVER_LEAVE = "buttonHoverLeave";

Button::Button(void)
{
    _pText = nullptr;
}

Button::~Button(void)
{
    term();
}

std::string Button::toString( void ) const
{
    return "Button";
}

void Button::init( Vector2 pos /*= Vector2::ZERO*/, string text /*= "Button"*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f */ )
{
    Unit::init(pos, origin, rot, blendColor, depth);

    _hover = false;
    _held  = false;

    Padding = Vector2(5.0f);

    TextColor   = Color::BLACK;
    BorderColor = Color::BLACK;
    BGColor     = Color::WHITE;

    HoverTextColor   = Color::WHITE;
    HoverBorderColor = Color::WHITE;
    HoverBGColor     = Color::BLACK;

    _pFont = Program::spDefaultFont;

    if (_pText == nullptr)
        delete _pText;

    _pText = New CachedText();
    _pText->init(text, _pFont);

    gpEventDispatcher->addEventListener(InputSystem::EVENT_MOUSE_MOVED, this, &Button::mouseMoved);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_MOUSE_BUTTON_PRESSED,  this, &Button::mouseButtonPressed);
    gpEventDispatcher->addEventListener(InputSystem::EVENT_MOUSE_BUTTON_RELEASED, this, &Button::mouseButtonReleased);
}

void Button::term( void )
{
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_MOUSE_MOVED, this, &Button::mouseMoved);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_MOUSE_BUTTON_PRESSED,  this, &Button::mouseButtonPressed);
    gpEventDispatcher->removeEventListener(InputSystem::EVENT_MOUSE_BUTTON_RELEASED, this, &Button::mouseButtonReleased);

    delete _pText;
    _pText = nullptr;
}

void Button::update( const Event& event )
{
    const FrameData* frameData = event.dataAs<FrameData>();

    if (_pText != nullptr)
        Size = _pText->size() + (Padding * 2.0f);
}

void Button::render( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    Color tmpBGColor, tmpBorderColor, tmpTextColor;

    if (_hover)
    {
        tmpBGColor     = HoverBGColor;
        tmpBorderColor = HoverBorderColor;
        tmpTextColor   = HoverTextColor;
    }
    else
    {
        tmpBGColor     = BGColor;
        tmpBorderColor = BorderColor;
        tmpTextColor   = TextColor;
    }

    renderTarget->fillRect(Rect(Pos, Size),       tmpBGColor,                Rot, Origin);
    renderTarget->drawRect(Rect(Pos, Size),       tmpBorderColor,            Rot, Origin);
    renderTarget->drawText(Pos + Padding, _pText, tmpTextColor, Align::LEFT, Rot, Origin);
}

void Button::setText( string text )
{
    if (_pText != nullptr)
        _pText->setText(text);
}

void Button::mouseMoved( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    if (bounds().containsPoint(data->Pos))
    {
        if (!_hover)
        {
            dispatchEvent(Event(Button::EVENT_BUTTON_HOVER_ENTER));
        }
        _hover = true;
    }
    else
    {
        if (_hover)
        {
            dispatchEvent(Event(Button::EVENT_BUTTON_HOVER_LEAVE));
        }
        _hover = false;
        _held = false;
    }
}

void Button::mouseButtonPressed( const Event& event )
{
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

void Button::mouseButtonReleased( const Event& event )
{
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
