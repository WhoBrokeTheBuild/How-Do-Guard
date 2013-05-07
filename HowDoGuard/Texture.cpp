#include "Texture.h"
#include "RenderTarget.h"
#include "CachedText.h"

Texture::Texture( void )
{
	_size = Rect::ZERO;
}

Texture::~Texture( void )
{
	term();
}

std::string Texture::toString( void ) const
{
	return "Texture";
}

void Texture::init( string filename )
{
	_filename = filename;

	SDL_Surface *surface = IMG_Load(_filename.c_str());

	init(surface);

	SDL_FreeSurface(surface);
}

void Texture::init( SDL_Surface* pSurface )
{
	generateTexture();

	_size = Rect(0.0f, 0.0f, (float)pSurface->w, (float)pSurface->h);

	int components;
	GLenum format;

	if (pSurface->format->Amask)
	{
		components = 4;
		format = GL_RGBA;
	}
	else
	{
		components = 3;
		format = GL_RGB;
	}

	gluBuild2DMipmaps(GL_TEXTURE_2D, components, (int)_size.Width, (int)_size.Height, format, GL_UNSIGNED_BYTE, pSurface->pixels);
}

void Texture::term( void )
{
	if (_texture != OPENGL_INVALID_TEXTURE)
		glDeleteTextures(1, &_texture);
}

void Texture::generateTexture( void )
{
	if (_texture != OPENGL_INVALID_TEXTURE)
		glDeleteTextures(1, &_texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,	  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,	  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}
