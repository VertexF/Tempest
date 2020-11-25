#ifndef APPLICTION_EVENTS_HDR
#define APPLICTION_EVENTS_HDR

#include <tempest_export.h>
#include <string>
#include <sstream>

#include "Event.h"

namespace Tempest
{
    class TEMPEST_EXPORT WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : Event(EVENT_CATEGORY_APPLICATION),
            _width(width), _height(height)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Window resize state: " << _width << " , " << _height;
            return ss.str();
        }

        static EventType getStaticType() { return EventType::WINDOW_RESIZE; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Window resize"; }
    public:
        unsigned int _width;
        unsigned int _height;
    };

    class TEMPEST_EXPORT WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() : Event(EVENT_CATEGORY_APPLICATION)
        {}

        static EventType getStaticType() { return EventType::WINDOW_CLOSED; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Window close"; }
    };

    class TEMPEST_EXPORT AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() : Event(EVENT_CATEGORY_APPLICATION)
        {}

        static inline EventType getStaticType() { return EventType::APP_UPDATE; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Application update"; }
    };

    class TEMPEST_EXPORT AppTickEvent : public Event
    {
    public:
        AppTickEvent() : Event(EVENT_CATEGORY_APPLICATION)
        {}

        static inline EventType getStaticType() { return EventType::APP_TICK; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Application tick"; }
    };

    class TEMPEST_EXPORT AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() : Event(EVENT_CATEGORY_APPLICATION)
        {}

        static inline EventType getStaticType() { return EventType::APP_RENDER; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Window render"; }
    };
}


#endif // !APPLICTION_EVENTS_HDR
