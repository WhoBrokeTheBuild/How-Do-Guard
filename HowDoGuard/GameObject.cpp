#include "GameObject.h"

GameObject::GameObject( void )
{
}

GameObject::~GameObject( void )
{
}

ostream& operator<<( ostream& os, const GameObject& go )
{
	os << go.toString();
	return os;
}

void *GameObject::operator new(size_t size)
{
	void* ptr = malloc(size);
	//gMemoryTracker.addAllocation((GameObject*)ptr, size);
	return ptr;
}
void *GameObject::operator new[](size_t size)
{
	void* ptr = malloc(size);
	//gMemoryTracker.addAllocation((GameObject*)ptr, size);
	return ptr;
}

void *GameObject::operator new(size_t pSize, int pLineNumber, char *pFilename)
{
	void* ptr = ::operator new(pSize);
	//gMemoryTracker.addAllocation((GameObject*)ptr, pSize, pLineNumber, pFilename);
	return ptr;
}

void *GameObject::operator new[](size_t pSize, int pLineNumber, char *pFilename)
{
	void* ptr = ::operator new(pSize);
	//gMemoryTracker.addAllocation((GameObject*)ptr, pSize, pLineNumber, pFilename);
	return ptr;
}

void GameObject::operator delete(void *pPtr, int pLineNumber, char *pFilename)
{
	::operator delete(pPtr);
	//gMemoryTracker.removeAllocation((GameObject*)pPtr);
	free(pPtr);
}

void GameObject::operator delete[](void *pPtr, int pLineNumber, char *pFilename)
{
	::operator delete(pPtr);
	//gMemoryTracker.removeAllocation((GameObject*)pPtr);
	free(pPtr);
}

void GameObject::operator delete(void *pPtr)
{
	//gMemoryTracker.removeAllocation((GameObject*)pPtr);
	free(pPtr);
}

void GameObject::operator delete[](void *pPtr)
{
	//gMemoryTracker.removeAllocation((GameObject*)pPtr);
	free(pPtr);
}