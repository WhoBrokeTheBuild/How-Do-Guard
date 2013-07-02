#include "Label.h"
#include "Program.h"

std::string Label::toString( void ) const
{
    return "Label";
}

void Label::init( Vector2 pos /*= Vector2::ZERO*/, string text /*= "Label"*/, Vector2 padding /*= Vector2::ZERO */ )
{
    Component::init(pos, padding);

    TextColor = Color::BLACK;

    _pText = New CachedText();
    _pText->init(text, Program::spDefaultFont);
}

void Label::term( void )
{
    delete _pText;
}

void Label::render( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    renderTarget->drawText(Pos + Padding, _pText, TextColor);
}
