#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include "PreComp.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"

namespace Tempest
{
    //TEMPEST_EXPORT void test();
    class TEMPEST_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        void onEvent(Event &e);
        void run();

    private:
        bool onWindowClosed(WindowClosedEvent &closed);

        bool _running;
        std::unique_ptr<Window> _window;
    };

    //To be defined in the client.
    Application* createApplication();
}

#endif // TEST_HDR
