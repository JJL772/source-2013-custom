/*

IEventSystem - A generic event system designed to replace the old GameEventManager used in source.
				The main target here is performance. The old event system is akin to a dictionary
				in python, or some other string-keyed data structure. Not exactly good for perf 
				if we were to deploy it widely in the engine. Being able to send events quickly
				to the client from the server is a must have for the new scripting system, as 
				user made modules rely on those events. There's simply no other way to interface
				with engine events without code access.

*/
#pragma once

#include "tier2/tier2.h"
#include "appframework/IAppSystem.h"
#include "utlbuffer.h"

#include <typeinfo>

/* 

Event types:
 - int types (8, 16, 32 and 64 bits)
 - float types (32 and 64 bits)
 - string type (fixed-width, 32 chars max incl. null terminator)
 
Notes:
 - Host and client most both be little endian systems. Not a problem unless we're targeting MIPS or some shit.

*/

#ifdef VALVE_BIG_ENDIAN
#error "You need to rewrite the event system serialization code for BE systems"
#endif 

template<size_t EventSize>
class CEventSerializeContext {
	byte m_bytes[EventSize];
	size_t m_pos = 0;
public:

	template<class T>
	void Write(const T& v);
	
	void Write<>(const byte& b) {
		m_bytes[m_pos++] = b;
	}
	
	void Write<>(const int16_t& i) {
		*((int16_t*)(m_bytes[m_pos])) = i;
		m_pos += sizeof(int16_t);
	}
	
	void Write<>(const int32_t& i) {
		*((int32_t*)(m_bytes[m_pos])) = i;
		m_pos += sizeof(int32_t);
	}
	
	void Write<>(const int64_t& i) {
		*((int64_t*)(m_bytes[m_pos])) = i;
		m_pos += sizeof(int64_t);
	}
	
	void Write<>(const float& f) {
		*((float*)(m_bytes[m_pos])) = i;
		m_pos += sizeof(float);
	}
	
	void Write<>(const double& d) {
		*((double*)(m_bytes[m_pos])) = d;
		m_pos += sizeof(double);
	}
	
	void Write<>(const char*& str) {
		size_t bytes = V_strlen(str);
		V_strncpy(&m_bytes[m_pos], str, 32);
		m_pos += bytes;
	}
};

template<size_t EventSize>
class CEventDeserializeContext {
	byte m_bytes[EventSize];
	size_t m_pos = 0;
public:

	template<class T>
	void Read(T& dst);
	
	void Read<>(byte& dst) {
		dst = m_bytes[m_pos++];
	}
	
	void Read<>(int16_t& dst) {
		dst = *(int16_t*)(&m_bytes[m_pos]);
		m_pos += sizeof(int16_t);
	}
	
	void Read<>(int32_t& dst) {
		dst = *(int32_t*)(&m_bytes[m_pos]);
		m_pos += sizeof(int32_t);
	}
	
	void Read<>(int64_t& dst) {
		dst = *(int64_t*)(&m_bytes[m_pos]);
		m_pos += sizeof(int64_t);
	}
	
	void Read<>(float& dst) {
		dst = *(float*)(&m_bytes[m_pos]);
		m_pos += sizeof(float);
	}
	
	void Read<>(double& dst) {
		dst = *(double*)(&m_bytes[m_pos]);
		m_pos += sizeof(double);
	}
	
	void Read<>(char(&dst)[32]) {
		auto len = V_strlen(&m_bytes[m_pos]);
		V_strncpy(dst, &m_bytes[m_pos], sizeof(dst));
		m_pos += len+1; // Account for null
	}
};

/** Flags for an IEventQueue **/
enum EventQueueFlags : uint32_t {
	EVQ_NONE = 0,            // No flags
	EVQ_NETWORKED = 1,       // Events passed to this queue should be networked to clients 
	EVQ_CLIENT = 2,          // This queue is on the client (cannot be networked in this case)
};

/** Flags for an IEvent **/
enum EventFlags : uint32_t {
	EV_NONE = 0,               // No flags
	EV_NO_NETWORKING = 1,      // If the queue has networking enabled, this event will not be networked
};

/** Listener prio. Listeners with the higher priority will be invoked first **/
enum class EventListenerPrio {
	HIGHEST = 0,
	HIGH,
	MEDIUM,
	LOW,
	DEFAULT = MEDIUM
};

class IEvent {
public:
	/** Returns the size of the event when serialized to a simple bytes structure **/
	virtual size_t GetSerializedSize() const = 0;
	
	/** Serializes the event into the provided buffer **/
	virtual void Serialize(void* pBuffer, size_t bufSize) = 0;
	
	/** Un-serializes the event from the specified buffer **/
	/** bufSize must equal GetSerializedSize **/
	virtual void UnSerialize(void* pBuffer, size_t bufSize) = 0;
	
	/** Returns the flags for the event **/
	virtual EventFlags GetFlags() const = 0;
	
	/** Returns the name of the event **/
	virtual const char* GetName() const = 0;
	
	template<class T>
	bool Is() const {
		return typeid(*this) == typeid(T);
	}
};

/** A simple game event listener class **/
class IEventListener {
public:
	/** Invoked when a game event should be handled **/
	/** Returning false will STOP the event from being handled elsewhere **/
	/** Returning true will ALLOW the event to be handled by other listeners **/
	virtual bool OnGameEvent(IEvent* pEvent) = 0;
	
	/** Returns the event listener priority **/
	virtual EventListenerPrio GetListenerPrio() const { return EventListenerPrio::DEFAULT; };
};

class IEventQueue {
public:

	/** Returns the name of the event queue, usually for debugging purposes **/
	virtual const char* GetName() const = 0;
	
	/** Registers an event listener **/
	virtual void RegisterListener(IEventListener* pListener) = 0;
	
	/** Unregisters an event listener **/
	virtual void UnregisterListener(IEventListener* pListener) = 0;
	
	/** Places an event into the rear of the queue **/
	virtual bool PostEvent(IEvent* pEvent) = 0;
	
	/** Returns the event at the front of the queue, optionally not removing it **/
	virtual IEvent* GetEvent(bool bRemove = true) = 0;
	
	/** Purges the entire event queue **/
	virtual void Purge() = 0;
	
	/** Checks if any events are pending **/
	virtual bool BPending() const = 0;
	virtual size_t GetNumPending() const = 0;
	
	virtual EventQueueFlags GetQueueFlags() const = 0;
	
	/** Removes each event from the queue and invokes event callbacks **/
	virtual void RunEventCallbacks() = 0;
	
	/** Disable the event queue. When disabled, the queue will drop all events given to it with PostEvent **/
	/** It will do nothing when RunEventCallbacks() is called either **/
	virtual void Disable() = 0;
	
	/** Puts the queue back into an enabled state **/
	virtual void Enable() = 0;
	virtual bool BEnabled() const = 0;
};

/** IEventSystem is a minimal interface that only handles management of created event queues **/
class IEventSystem : IAppSystem {
public:
	
	/** Creates a new event queue with the specified flags and name **/
	virtual IEventQueue* CreateQueue(const char* pName, EventQueueFlags flags) = 0;
	
	/** Destroys an event queue **/
	/** Does not invoke event handles for the remaining events **/
	virtual void DestroyQueue(IEventQueue* pQueue) = 0;
	
	/** Tries to find a queue, returns nullptr if it doesn't exist **/
	virtual IEventQueue* FindQueue(const char* pName) = 0;
};

template<class...T>
class Event : public IEvent {
public:
	

};