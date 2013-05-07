#include "MemoryTracker.h"

int MemoryTracker::_sAllocationIndex = 0;
MemoryTracker gMemoryTracker;

MemoryTracker::MemoryTracker( void )
{
}

MemoryTracker::~MemoryTracker( void )
{

#ifdef DEBUG

	INF(toString(), "Final Allocations");
	printAllocations();

#endif

}

std::string MemoryTracker::toString( void ) const
{
	return "Memory Tracker";
}

void MemoryTracker::addAllocation( GameObject *ptr, size_t size, int lineNumber, char *filename )
{
	map<GameObject*, AllocationRecord>::iterator it = _allocations.find(ptr);
	
	if (it != _allocations.end())
	{
		ERR(toString(), "Element already in map");
	}
	else
	{
		AllocationRecord rec(_sAllocationIndex, size, lineNumber, string(filename));

		pair<GameObject*, AllocationRecord> newPair(ptr, rec);
		_allocations.insert(newPair);

		++_sAllocationIndex;
	}
}

bool MemoryTracker::removeAllocation( GameObject *ptr )
{
	map<GameObject*, AllocationRecord>::iterator it = _allocations.find(ptr);

	if (it == _allocations.end())
	{
		return false;
	}
	else
	{
		_allocations.erase(it);
	}

	return true;
}

int MemoryTracker::numAllocations( void )
{
	return _allocations.size();
}

void MemoryTracker::printAllocations( void )
{
	printAllocations(cout);
}

void MemoryTracker::printAllocations( ostream& stream )
{
	stream << "Allocations: \n";

	map<GameObject*, AllocationRecord>::iterator it;
	for (it = _allocations.begin(); it != _allocations.end(); ++it)
	{
		stream << "#" << it->second.Num
			   << ": (address: #" << it->first << ") "
			   << it->first->toString() << "\n";

		stream << "\t In " << basename(it->second.Filename)
			   << " On Line " << it->second.LineNum << "\n";
	}
}