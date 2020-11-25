#ifndef EVENT_HDR
#define EVENT_HDR

#include <tempest_export.h>
#include <string>
#include <functional>
#include <ostream>

namespace Tempest
{
    enum class EventType
    {
        None = 0,
        WINDOW_CLOSED, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_FOCUS_LOST, WINDOW_MOVED,
        APP_TICK, APP_UPDATE, APP_RENDER,
        KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOVED_MOUSE, MOUSED_SCROLLED
    };

    enum EventCategory
    {
        //(1 << 0) magic numbers need to be refactored.
        None = 0,
        EVENT_CATEGORY_APPLICATION = (1 << 0),
        EVENT_CATEGORY_INPUT =       (1 << 1),
        EVENT_CATEGORY_KEYBOARD =    (1 << 2),
        EVENT_CATEGORY_MOUSE =       (1 << 3),
        EVENT_CATEGORY_MOUSEBUTTON = (1 << 4)
    };

    class TEMPEST_EXPORT Event
    {
    public:
        Event(int category) : category(category)
        {
        }
        virtual ~Event() = default;

        bool isHandled = false;

        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlag() const { return category; }
        virtual std::string toString() const { return getName(); }

        bool isInCategory(EventCategory category)
        {
            return getCategoryFlag() & category;
        }

    protected:
        int category;
    };

    class EventDispatcher 
    {
        template<typename T>
        using eventFu = std::function<bool(T&)>;

    public:
        EventDispatcher(Event &events) : _event(events)
        {
        }

        template<typename T>
        bool dispatch(eventFu<T> func)
        {
            if (_event.getEventType() == T::getEventType()) 
            {
                _event.isHandled = func(*(T*)&_event);
                return true;
            }

            return false;
        }
    private:
        Event &_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) 
    {
        return os << e.toString();
    }
}

#endif // !EVENT_HDR