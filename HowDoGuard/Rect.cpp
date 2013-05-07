#include "Rect.h"

Rect Rect::ONE = Rect(1, 1, 1, 1);
Rect Rect::ZERO = Rect(0, 0, 0, 0);

Rect::Rect( float x, float y, float width, float height )
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
}

Rect::Rect(void)
{
	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;
}

Rect::~Rect(void)
{
}
