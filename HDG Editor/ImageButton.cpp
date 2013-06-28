#include "ImageButton.h"

ImageButton::ImageButton(void)
{
}

ImageButton::~ImageButton(void)
{
    term();
}

std::string ImageButton::toString( void ) const
{
    return "Image Button";
}

void ImageButton::init( Vector2 pos /*= Vector2::ZERO*/, Sprite* image /*= nullptr*/, Sprite* hoverImage /*= nullptr*/, Vector2 padding /*= Vector2::ZERO*/ )
{
    Button::init(pos, padding);

    if (hoverImage == nullptr)
        hoverImage = image;

    _pImage = image;
    _pHoverImage = hoverImage;

    BlendColor      = Color::WHITE;
    HoverBlendColor = Color::WHITE;
}

void ImageButton::term( void )
{
}

Size ImageButton::size( void )
{
    return (_hover ? _pHoverImage->SourceRect.size() : _pImage->SourceRect.size());
}

void ImageButton::render( const Event& event )
{
    Button::render(event);

    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    Texture* texture = (_hover ? _pHoverImage->texture()  : _pImage->texture());
    Rect     source  = (_hover ? _pHoverImage->SourceRect : _pImage->SourceRect);
    Color    color   = (_hover ? HoverBlendColor          : BlendColor);

    renderTarget->draw(Pos + Padding, texture, source, color);
}