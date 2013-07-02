#include "Dropdown.h"
#include "Program.h"

const EventType Dropdown::EVENT_SELECTED_INDEX_CHANGED = "eventDropdownSelectedIndexChanged";

Dropdown::~Dropdown(void)
{
    term();
}

std::string Dropdown::toString( void ) const
{
    return "Dropdown";
}

void Dropdown::init( Vector2 pos /*= Vector2::ZERO*/, vector<string> items /*= vector<string>()*/,Vector2 padding /*= Vector2(5.0f)*/ )
{
    Component::init(pos, padding);

    Items   = items;
    MaxRows = -1;

    _listShown = false;

    _leftTrianglePadding = 10.0f;

    TextColor   = Color::BLACK;
    BorderColor = Color::BLACK;
    BGColor     = Color::WHITE;

    FocusTextColor   = Color::WHITE;
    FocusBorderColor = Color::WHITE;
    FocusBGColor     = Color::BLACK;

    _pFont = Program::spDefaultFont;
    _pText = New CachedText();
    _pText->init(" ", _pFont);
}

void Dropdown::term( void )
{
    delete _pText;
}

void Dropdown::update( const Event& event )
{
    Component::update(event);
}

void Dropdown::render( const Event& event )
{
    const RenderData* renderData = event.dataAs<RenderData>();
    RenderTarget* renderTarget = renderData->renderTarget();

    Color 
        tmpBGColor,
        tmpBorderColor,
        tmpTextColor;

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

    Size largest = largestItem();
    Rect drawBounds = Rect(Pos, (Padding * 2.0f) + largest + Size(_leftTrianglePadding, 0.0f));

    renderTarget->fillRect(drawBounds, tmpBGColor);
    renderTarget->drawRect(drawBounds, tmpBorderColor);
    renderTarget->fillTriangle(Pos + Padding + Vector2(2.0f, 7.0f), 5.0f, tmpBorderColor, (float)PI);

    if (inBounds(Index, 0, (int)Items.size() - 1))
    {
        _pText->setText(Items[Index]);
        renderTarget->drawText(Pos + Padding + Vector2(_leftTrianglePadding, 0.0f), _pText, tmpTextColor, Align::ALIGN_LEFT);
    }

    if (_listShown)
    {
        Size step = largest + (Padding * 2.0f);
        Vector2 offset = Vector2(0.0f, step.height());

        int row = 0,
            col = 0;
        for (unsigned int i = 0; i < Items.size(); ++i)
        {
            if (row == 0)
            {
                Rect listBounds = Rect(Pos + offset, Vector2(step.width(), size().height() - offset.Y));
                renderTarget->fillRect(listBounds, tmpBGColor);
                renderTarget->drawRect(listBounds, tmpBorderColor);
            }

            ++row;
            if (MaxRows != -1 && row >= MaxRows)
            {
                row = 0;
                ++col;
                offset.Y = step.height();
                offset.X += step.width();
            }
        }

        offset = Vector2(0.0f, step.height());

        row = col = 0;
        for (unsigned int i = 0; i < Items.size(); ++i)
        {
            _pText->setText(Items[i]);
            renderTarget->drawText(Pos + Padding + offset, _pText, tmpTextColor, Align::ALIGN_LEFT);
            offset.Y += step.height();

            ++row;
            if (MaxRows != -1 && row >= MaxRows)
            {
                row = 0;
                ++col;
                offset.Y = step.height();
                offset.X += step.width();
            }
        }
    }
}

Size Dropdown::largestItem( void )
{
    Size largest = Size::ZERO;

    for (unsigned int i = 0; i < Items.size(); ++i)
    {
        Size curr = _pFont->measureString(Items[i]);

        if (curr.X > largest.X)
            largest.X = curr.X;

        if (curr.Y > largest.Y)
            largest.Y = curr.Y;
    }

    if (largest == Size::ZERO)
        largest = _pFont->measureString(" ");

    return largest;
}

Size Dropdown::size( void )
{
    Size ret = largestItem() + (Padding * 2.0f) + Vector2(_leftTrianglePadding, 0.0f);

    if (_listShown)
    {
        ret.Y += (largestItem().height() + (Padding.Y * 2.0f)) * (MaxRows != -1 ? min(MaxRows, (int)Items.size()) : Items.size());
        ret.X += (largestItem().width() + (Padding.X * 2.0f)) * ((MaxRows != -1 ? Items.size() % MaxRows : 1) - 1);
    }

    return ret;
}

void Dropdown::clickedOn( Vector2 mousePos )
{
    Component::clickedOn(mousePos);

    if (_listShown)
    {
        Vector2 clickPos = mousePos - Pos;

        int index = (int)((mousePos - Pos).Y / (largestItem().height() + (Padding.Y * 2.0f))) - 1;

        if (MaxRows != -1)
        {
            index += (int)((mousePos - Pos).X / (largestItem().width() + (Padding.X * 2.0f))) * MaxRows;
        }

        if (index >= (int)Items.size())
            index = -1;

        if (Index != index)
        {
            Index = index;
            dispatchEvent(Event(EVENT_SELECTED_INDEX_CHANGED, DropdownChangedData(Index, selected())));
        }

        _listShown = false;
    }
    else
    {
        _listShown = true;
    }
}

void Dropdown::clickedOff( Vector2 mousePos )
{
    Component::clickedOff(mousePos);

    _listShown = false;
}

std::string Dropdown::selected( void )
{
    if (inBounds(Index, 0, (int)Items.size() - 1))
    {
        return Items[Index];
    }
    return "";
}
