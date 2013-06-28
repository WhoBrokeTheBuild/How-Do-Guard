#include "TextButton.h"
#include "Program.h"

TextButton::TextButton(void)
{
}

TextButton::~TextButton(void)
{
    term();
}

std::string TextButton::toString( void ) const
{
    return "Text Button";
}

void TextButton::init( Vector2 pos /*= Vector2::ZERO*/, string text /*= "Button"*/, Vector2 padding /*= Vector2::ZERO*/ )
{
    Button::init(pos, padding);

    TextColor   = Color::BLACK;
    BorderColor = Color::BLACK;
    BGColor     = Color::WHITE;

    HoverTextColor   = Color::WHITE;
    HoverBorderColor = Color::WHITE;
    HoverBGColor     = Color::BLACK;

    _pFont = Program::spDefaultFont;

    _pText = New CachedText();
    _pText->init(text, _pFont);
}

void TextButton::term( void )
{
    delete _pText;
}

void TextButton::render( const Event& event )
{
    Button::render(event);

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

    renderTarget->fillRect(bounds(), tmpBGColor);
    renderTarget->drawRect(bounds(), tmpBorderColor);

    renderTarget->drawText(Pos + Padding, _pText, tmpTextColor, Align::ALIGN_LEFT);
}

Size TextButton::size( void )
{
    return _pText->size() + (Padding * 2.0f);
}

void TextButton::setText( string text )
{
    _pText->setText(text);
}

std::string TextButton::text( void )
{
    return _pText->text();
}
