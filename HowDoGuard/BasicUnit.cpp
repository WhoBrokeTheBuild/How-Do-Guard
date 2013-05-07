#include "BasicUnit.h"


BasicUnit::BasicUnit(void)
{
}


BasicUnit::~BasicUnit(void)
{
}

std::string BasicUnit::toString( void ) const
{
	return "Basic Unit";
}

void BasicUnit::init( Animation* pAnimation /*= nullptr*/, Vector2 pos /*= Vector2::ZERO*/, Vector2 origin /*= Vector2::ZERO*/, float rot /*= 0.0f*/, Color blendColor /*= Color::WHITE*/, float depth /*= 1.0f*/ )
{
	_frame = 0;
	setAnimation(pAnimation, true);
	Pos = pos;
	Origin = origin;
	Rot = rot;
	BlendColor = blendColor;
	Depth = depth;
}

void BasicUnit::term( void )
{
}

void BasicUnit::update( GameTime *pGameTime )
{
	if (Animating && !(Looping && _animationComplete))
	{
		updateAnimation(pGameTime);
	}
}

void BasicUnit::draw( RenderTarget *pRenderTarget, Vector2 offset /*= Vector2::ZERO */ )
{
	Sprite *currentFrame = _pAnimation->frame(_frame);

	if (currentFrame == nullptr)
		return;

	pRenderTarget->draw(Pos + offset, currentFrame->texture(), currentFrame->SourceRect, BlendColor, Rot, Origin);
}

void BasicUnit::setAnimation( Animation *pAnimation, bool useDefaults /*= true*/ )
{
	_pAnimation = pAnimation;

	if (useDefaults)
	{
		_animationTimeout = pAnimation->frame(_frame)->FrameTime;
		Animating = pAnimation->Animating;
		Looping = pAnimation->Looping;
		_animationComplete = false;
	}
}

void BasicUnit::updateAnimation( GameTime *pGameTime )
{
	_animationTimeout -= pGameTime->elapsedMilliseconds();
	if (_animationTimeout < 0)
	{
		if (!Looping)
		{
			if (_frame == _pAnimation->length() - 1)
			{
				_frame = clamp(_frame, 0, _pAnimation->length() - 1);
				_animationComplete = true;
				return;
			}
		}
		_frame = (_frame + 1) % _pAnimation->length();
		_animationTimeout = _pAnimation->frame(_frame)->FrameTime;
	}
}
