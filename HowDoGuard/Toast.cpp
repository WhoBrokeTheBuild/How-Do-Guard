#include "Toast.h"
#include "InputSystem.h"

Toast::Toast( void )
{
}

Toast::~Toast (void )
{
	term();
}

std::string Toast::toString( void ) const
{
	return "Toast";
}

void Toast::init( void )
{
	BasicUnit::init(gpDataManager->pAnimations->get("toast-ghp"), Vector2(100));

	_vel = Vector2::ZERO;

	gpEventDispatcher->addEventListener(InputSystem::INPUT_EVENT, this, &Toast::input);
}

void Toast::term( void )
{
	BasicUnit::term();
}

void Toast::update( const Event& event )
{
	BasicUnit::update(event);

	Pos += _vel;
}

void Toast::input( const Event& event )
{
	const InputData* inputData = event.dataAs<InputData>();

}