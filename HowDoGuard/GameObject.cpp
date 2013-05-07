#include "GameObject.h"

GameObject::GameObject(void)
{
}

GameObject::~GameObject( void )
{
}

ostream& operator<<( ostream& os, const GameObject& go )
{
	os << go.toString() << "\n";
	return os;
}
