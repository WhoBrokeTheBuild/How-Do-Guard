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
	BasicUnit::init(gpDataManager->pAnimations->get("toast-ghp"), Vector2(300, 200));

	_vel = Vector2::ZERO;

	gpEventDispatcher->addEventListener(InputSystem::EVENT_INPUT_PRESSED, this, &Toast::input);
}

void Toast::term( void )
{
	BasicUnit::term();

	gpEventDispatcher->removeEventListener(InputSystem::EVENT_INPUT_PRESSED, this, &Toast::input);
}

void Toast::update( const Event& event )
{
	BasicUnit::update(event);

	Pos += _vel;
	_vel.X = _vel.Y = 0;
}

void Toast::input( const Event& event )
{
	const InputData* inputData = event.dataAs<InputData>();


}