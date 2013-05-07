#include "RenderTarget.h"
#include "GraphicsSystem.h"

RenderTarget::RenderTarget( void )
{
}

RenderTarget::~RenderTarget( void )
{
}

void RenderTarget::init( GraphicsSystem *pGraphicsSystem )
{
	_pGraphicsSystem = pGraphicsSystem;
}

void RenderTarget::term( void )
{

}

std::string RenderTarget::toString( void ) const
{
	return "Render Target";
}

void RenderTarget::beginDraw( void )
{
	Color clearColor = _pGraphicsSystem->clearColor();

	glClearColor(clearColor.getR(), clearColor.getG(), clearColor.getB(), clearColor.getA());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
}

void RenderTarget::endDraw( void )
{
	SDL_GL_SwapBuffers();
}

// ShapeValue 1.5 - Draws Triangle
// ShapeValue 2   - Draws Square
// ShapeValue 3   - Draws Hexagon
// ShapeValue 4   - Draws Octagon
// ShapeValue 5   - Draws Decagon
// ShapeValue 6   - Draws Circle
// ShapeValue 12  - Draws Better Circle
void RenderTarget::drawShape( float x, float y, float radius, float shapeValue, Color color, float rotation /*= 0.0f*/ )
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);

	glBegin(GL_LINE_LOOP);

	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());

	for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
	{
		glVertex3f(cosf(i) * radius, sinf(i) * radius, 0.0f);
	}

	glEnd();

	glPopMatrix();
}

void RenderTarget::fillShape( float x, float y, float radius, float shapeValue, Color color, float rotation /*= 0.0f*/ )
{
	glPushMatrix();
	glTranslatef(x, y, 0.0f);

	glRotatef((float)toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);

	glBegin(GL_POLYGON);

	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());

	for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
	{
		glVertex3f(cosf(i) * radius, sinf(i) * radius, 0.0f);
	}

	glEnd();

	glPopMatrix();
}

void RenderTarget::drawRect( float x, float y, float width, float height, Color color, float rotation /*= 0.0f*/ )
{
	Rect rect = Rect(x, y, width, height);
	drawRect(rect, color, rotation);
}

void RenderTarget::drawRect( Rect rect, Color color, float rotation /*= 0.0f*/ )
{
	glPushMatrix();
	glTranslatef(rect.X, rect.Y, 0);

	glRotatef((float)toDeg(rotation), 0.0f, 0, 1.0f);

	glBegin(GL_LINE_LOOP); 

	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());

	glVertex3f(0.0f,       0.0f,        0.0f);
	glVertex3f(rect.Width, 0.0f,        0.0f);
	glVertex3f(rect.Width, rect.Height, 0.0f);
	glVertex3f(0.0f,       rect.Height, 0.0f);

	glEnd(); 

	glPopMatrix();
}

void RenderTarget::fillRect( float x, float y, float width, float height, Color color, float rotation /*= 0.0f*/ )
{
	Rect rect = Rect(x, y, width, height);
	fillRect(rect, color, rotation);
}

void RenderTarget::fillRect( Rect rect, Color color, float rotation /*= 0.0f*/ )
{
	glPushMatrix();
	glTranslatef(rect.X, rect.Y, 0);

	glRotatef((float)toDeg(rotation), 0.0f, 0, 1.0f);

	glBegin(GL_QUADS);

	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());

	glVertex3f(0.0f,       0.0f,        0.0f);
	glVertex3f(rect.Width, 0.0f,        0.0f);
	glVertex3f(rect.Width, rect.Height, 0.0f);
	glVertex3f(0.0f,       rect.Height, 0.0f);

	glEnd();

	glPopMatrix();
}

void RenderTarget::drawCircle( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	Circle circle = Circle(x, y, radius);
	drawCircle(circle, color, rotation);
}

void RenderTarget::drawCircle( Circle circle, Color color, float rotation /*= 0.0f*/ )
{
	drawShape(circle.X, circle.Y, circle.Radius, 12, color, rotation);
}

void RenderTarget::fillCircle( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	Circle circle = Circle(x, y, radius);
	fillCircle(circle, color, rotation);
}

void RenderTarget::fillCircle( Circle circle, Color color, float rotation /*= 0.0f*/ )
{
	fillShape(circle.X, circle.Y, circle.Radius, 12, color, rotation);
}

void RenderTarget::drawTriangle( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	drawShape(x, y, radius, 1.5, color, rotation);
}

void RenderTarget::fillTriangle( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	fillShape(x, y, radius, 1.5, color, rotation);
}

void RenderTarget::drawPentagon( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	drawShape(x, y, radius, 2.5, color, rotation);
}

void RenderTarget::fillPentagon( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	fillShape(x, y, radius, 2.5, color, rotation);
}

void RenderTarget::drawHexagon( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	drawShape(x, y, radius, 3, color, rotation);
}

void RenderTarget::fillHexagon( float x, float y, float radius, Color color, float rotation /*= 0.0f*/ )
{
	fillShape(x, y, radius, 3, color, rotation);
}