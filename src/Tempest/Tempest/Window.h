#ifndef WINDOW_HDR
#define WINDOW_HDR

#include "PreComp.h"

#include "Events/Event.h"

namespace Tempest 
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string title = "Tempest Engine",
                    unsigned int w = 1280,
                    unsigned int h = 720) :
            title(title), width(w), height(h)
        {
        }
    };

    //This is just an interface class for how you should write platform windowing.
    class TEMPEST_EXPORT Window 
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void onUpdate() = 0;

        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        //Window attributes.
        virtual void setCallbackFunction(const EventCallbackFunc &callback) = 0;
        virtual void setVSync() = 0;
        virtual bool isVSync() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
}

#endif // !WINDOW_HDR
