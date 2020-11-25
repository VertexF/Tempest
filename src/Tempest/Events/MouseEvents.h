#ifndef MOUSE_EVENTS_HDR
#define MOUSE_EVENTS_HDR

#include "PreComp.h"

#include "Event.h"

namespace Tempest
{
    class TEMPEST_EXPORT MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : Event(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT),
            x(x), y(y) 
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouses position: " << x << " , " << y;
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::MOVED_MOUSE; }
        inline EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Mouse Moved"; }
    public:
        float x;
        float y;
    };

    class TEMPEST_EXPORT MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float x, float y) : Event(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT),
            x(x), y(y)
        {
        }

            std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouses scroll position: " << x << " , " << y;
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::MOUSED_SCROLLED; }
        inline EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Mouse Moved"; }
    public:
        float x;
        float y;
    };

    class TEMPEST_EXPORT MouseButtonEvent : public Event
    {
    public:
        inline int getMouseEvent() const { return _button; }

    protected:
        MouseButtonEvent(int button) : Event(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT),
            _button(button)
        {
        }

        int _button;
    };

    class TEMPEST_EXPORT MouseButtonEventPressed : public MouseButtonEvent
    {
    public:
        MouseButtonEventPressed(int button) : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse button pressed state: " << _button;
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::MOUSE_BUTTON_PRESSED; }
        inline EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Mouse button pressed"; }
    };

    class TEMPEST_EXPORT MouseButtonEventReleased : public MouseButtonEvent
    {
    public:
        MouseButtonEventReleased(int button) : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse button released state: " << _button;
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::MOUSE_BUTTON_RELEASED; }
        inline EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Mouse button released"; }
    };

}

#endif // !MOUSE_EVENTS_HDR
