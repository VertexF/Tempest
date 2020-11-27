#ifndef KEY_EVENTS_HDR
#define KEY_EVENTS_HDR

#include "PreComp.h"

#include "Event.h"

namespace Tempest
{
    class TEMPEST_EXPORT KeyEvent : public Event
    {
    public:
        inline int getKeyCode() const { return keyCode; }

    protected:
        KeyEvent(int keyCode) : Event(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT), keyCode(keyCode)
        {
        }

        int keyCode;
    };

    class TEMPEST_EXPORT PressedKeyEvent : public KeyEvent 
    {
    public:
        PressedKeyEvent(int keyCode, int repeats) : KeyEvent(keyCode), _repeatedNum(repeats)
        {
        }

        inline int getTimeseRepeated() const { return _repeatedNum; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key pressed: " << keyCode << " (" << _repeatedNum << " repeats)";
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::KEY_PRESSED; }
        inline EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Key Pressed"; }
    private:
        int _repeatedNum;
    };

    class TEMPEST_EXPORT ReleasedKeyEvent : public KeyEvent
    {
    public:
        ReleasedKeyEvent(int keyCode) : KeyEvent(keyCode)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key released: " << keyCode;
            return ss.str();
        }

        static inline EventType getStaticType() { return EventType::KEY_RELEASED; }
        virtual EventType getEventType() const override { return getStaticType(); };
        virtual const char* getName() const override { return "Key Released"; }
    };
}

#endif // !KEY_EVENTS_HDR
