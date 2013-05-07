#pragma once

#ifndef __EVENT_H__
#define __EVENT_H__

#include "Common.h"
#include "GameObject.h"

#include "EventData.h"

typedef string EventType;

class EventDispatcher;

class Event :
	public GameObject
{

	friend class EventDispatcher;

protected:

	EventDispatcher
		*_pEventTarget;

	EventType
		_type;

	EventData
		*_pData;

public:

	static const EventType EVENT_NULL;
	static const EventType EVENT_GAME_END;
	static const EventType EVENT_GAME_START;

	static const Event BLANK_EVENT;
	static const EventData BLANK_DATA;

	Event(const EventType &type = EVENT_NULL, const EventData &data = BLANK_DATA);
	Event(const Event &rhs);
	virtual ~Event(void);

	virtual string toString( void ) const;

	inline EventType type( void ) const { return _type; };
	inline EventDispatcher *target( void ) const { return _pEventTarget; };

	template <typename T>
	inline T* targetAs( void ) const { return dynamic_cast<T*>(_pEventTarget); };

	inline const EventData *data( void ) const { return _pData; };

	template <typename T>
	inline const T* dataAs( void ) const { return dynamic_cast<const T*>(_pData); };

};

#endif