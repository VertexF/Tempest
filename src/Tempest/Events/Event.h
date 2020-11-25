#ifndef EVENT_HDR
#define EVENT_HDR

#include <string>
#include <functional>
#include <tempest_export.h>

namespace Tempest
{
    enum class EventType
    {
        NONE = 0,
        WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_FOCUS_LOST, WINDOW_MOVED,
        APP_TICK, APP_UPDATE, APP_RENDER,
        KEY_PRESSED, KEY_RELEASED,
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
    };

    enum EventTypeCatgory
    {
        //Maybe consider adding the bit shifts into a maths function inside core.h
        None = 0,
        EVENT_CATEGORY_APPLICATION = (1 << 0),
        EVENT_CATEGORY_INPUT = (1 << 1),
        EVENT_CATEGORY_KEYBOARD = (1 << 2),
        EVENT_CATEGORY_MOUSE = (1 << 3),
        EVENT_CATEGORY_MOUSEBUTTON = (1 << 4)
    };

    class TEMPEST_EXPORT Events
    {
        friend  class EventDispatcher;
    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlag() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(int category)
        {
            return getCategoryFlag() & category;
        }
    protected:
        bool isHandled;
    };
}
}

#endif // !EVENT_HDR
