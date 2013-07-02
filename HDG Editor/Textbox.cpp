#include "Textbox.h"
#include "Program.h"

Textbox::Textbox(void)
{
}

Textbox::~Textbox(void)
{
    term();
}

std::string Textbox::toString( void ) const
{
    return "Textbox";
}

void Textbox::init( Vector2 pos /*= Vector2::ZERO*/, float width /*= 100*/, Vector2 padding /*= Vector2(5.0f)*/ )
{
    Component::init(pos, padding);
    ITextInputListener::init();

    _width = width;

    _cursorPos = 0;
    _textPos   = 0;

    _cursorShown = false;
    _cursorSpeed = 500;
    _cursorTimeout = _cursorSpeed;

    TextColor   = Color::BLACK;
    BorderColor = Color::BLACK;
    BGColor     = Color::WHITE;

    FocusTextColor   = Color::WHITE;
    FocusBorderColor = Color::WHITE;
    FocusBGColor     = Color::BLACK;

    _pFont = Program::spDefaultFont;

    _cachedChars = map<char, CachedText*>();
    _maxCharSize = Size::ZERO;

    CachedText* curr;
    stringstream ss;
    for (char ch = 0; ch < CHAR_MAX; ++ch)
    {
        ss.str("");
        ss << ch;

        _cachedChars.insert(pair<char, CachedText*>(ch, New CachedText()));
        curr = _cachedChars[ch];

        curr->init(ss.str(), _pFont);

        if (curr->size().width() > _maxCharSize.width())
            _maxCharSize.X = curr->size().width();

        if (curr->size().height() > _maxCharSize.height())
            _maxCharSize.Y = curr->size().height();
    }
}

void Textbox::term( void )
{
    for (char ch = 0; ch < CHAR_MAX; ++ch)
    {
        delete _cachedChars[ch];
    }
    _cachedChars.clear();
}

Size Textbox::size( void )
{
    return Size(_width, _maxCharSize.height()) + (Padding * 2.0f);
}

void Textbox::update( const Event& event )
{
    const FrameData* frameData = event.dataAs<FrameData>();

    _charWidth = (int)(size().width() / _maxCharSize.width());

    if (Focus)
    {
        _cursorTimeout -= frameData->elapsedMilliseconds();
        if (_cursorTimeout < 0)
        {
            _cursorTimeout = _cursorSpeed;
            _cursorShown = !_cursorShown;
        }
    }
}

void Textbox::render( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    Color 
        tmpBGColor,
        tmpBorderColor,
        tmpTextColor;

    Vector2
        textOff,
        cursorOff,
        textSize;

    Rect
        clipRect;

    if (Focus)
    {
        tmpBGColor     = FocusBGColor;
        tmpBorderColor = FocusBorderColor;
        tmpTextColor   = FocusTextColor;
    }
    else
    {
        tmpBGColor     = BGColor;
        tmpBorderColor = BorderColor;
        tmpTextColor   = TextColor;
    }

    renderTarget->fillRect(bounds(), tmpBGColor);
    renderTarget->drawRect(bounds(), tmpBorderColor);

    Vector2 charPos = Pos + Padding;

    CachedText* cachedChar;
    for (unsigned int i = _textPos; i < _charWidth + _textPos; ++i)
    {
        if (i >= Text.length())
            break;

        cachedChar = _cachedChars[Text[i]];
        renderTarget->drawText(charPos, cachedChar, tmpTextColor, ALIGN_LEFT);
        charPos.X += _maxCharSize.width();
    }

    if (_cursorShown)
    {
        cursorOff = Vector2(_maxCharSize.width() * (_cursorPos - _textPos), 0);
        cursorOff += Pos + Padding + Vector2(1, 0); // For Spacing

        renderTarget->drawLine(cursorOff, cursorOff + Vector2(0, _maxCharSize.height()), tmpTextColor);
    }
}

void Textbox::insert( char ch )
{
    string newStr = "";

    unsigned int textLength = Text.length();

    if (_cursorPos > textLength)
        _cursorPos = textLength;

    bool found = false;

    for (unsigned int i = 0; i <= textLength; ++i)
    {
        if (!found && i == _cursorPos)
        {
            newStr += ch;
            _cursorPos++;
            checkTextPos();

            found = true;
        }
        
        if (i < textLength)
        {
            newStr += Text[i];
        }
    }

    Text = newStr;
}

void Textbox::remove( bool before /*= true */ )
{
    string newStr = "";

    unsigned int textLength = Text.length();

    if (_cursorPos > textLength)
        _cursorPos = textLength;

    bool found = false;

    for (unsigned int i = 0; i <= textLength; ++i)
    {
        if (!found)
        {
            if (before && i == _cursorPos - 1)
            {
                _cursorPos--;
                checkTextPos();

                found = true;
                continue;;
            }
            else if (!before && i == _cursorPos)
            {
                found = true;
                continue;;
            }

        }

        if (i < textLength)
        {
            newStr += Text[i];
        }
    }

    Text = newStr;
}

void Textbox::textInputChar( const Event& event )
{
    const TextInputData *data = event.dataAs<TextInputData>();

    if (!Focus)
        return;

    insert(data->Char);
}

void Textbox::textInputBackspace( const Event& event )
{
    if (!Focus)
        return;

    remove(true);
}

void Textbox::textInputDelete( const Event& event )
{
    if (!Focus)
        return;

    remove(false);
}

void Textbox::textInputArrows( const Event& event )
{
    const TextInputData *data = event.dataAs<TextInputData>();

    if (!Focus)
        return;

    if (data->Dir == DIR_WEST)
    {
        if (_cursorPos > 0)
        {
            --_cursorPos;
            checkTextPos();
        }
    }
    else if (data->Dir == DIR_EAST)
    {
         if (_cursorPos < Text.length())
         {
             ++_cursorPos;
             checkTextPos();
         }
    }
}

void Textbox::textInputHomeEnd( const Event& event )
{
    const TextInputData *data = event.dataAs<TextInputData>();

    if (!Focus)
        return;

    if (data->Dir == DIR_WEST)
    {
        _cursorPos = 0;
        _textPos   = 0;
    }
    else if (data->Dir == DIR_EAST)
    {
        _cursorPos = Text.length();
        checkTextPos();
    }
}

void Textbox::checkTextPos( void )
{
    if (_cursorPos < _textPos)
    {
        _textPos = max((int)_cursorPos - 1, 0);
    }
    else if (_cursorPos > _textPos + _charWidth)
    {
        _textPos = min(_cursorPos - _charWidth, Text.length() - _charWidth) + 1;
    }
}

void Textbox::clickedOn( Vector2 mousePos )
{
    Component::clickedOn(mousePos);

    _cursorShown = true;
    _cursorTimeout = _cursorSpeed;
}

void Textbox::clickedOff( Vector2 mousePos )
{
    Component::clickedOff(mousePos);

    _cursorShown = false;
}