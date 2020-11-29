#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include "PreComp.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "LayerStack.h"

namespace Tempest
{
    class Layer;

    //This is the main coordinator class.
    class TEMPEST_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        void onEvent(Event &e);
        void run();

        void pushLayer(Layer *layer);
        void pushOverlay(Layer *layer);
    private:
        bool onWindowClosed(WindowClosedEvent &closed);

        bool _running;
        std::unique_ptr<Window> _window;
        LayerStack _layerStack;
    };

    //To be defined in the client. This is how you use the shared library.
    Application* createApplication();
}

#endif // TEST_HDR
