#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include "PreComp.h"
#include "Window.h"
#include "Tempest/Events/Event.h"
#include "Tempest/Events/ApplicationEvents.h"
#include "LayerStack.h"
#include "Tempest/ImGui/ImGUILayer.h"

#include "TimeStep.h"

namespace Tempest
{
    class Layer;

    //This is the main coordinator class.
    class Application
    {
    public:
        Application(const std::string& title = "Tempest Engine");
        virtual ~Application();

        void onEvent(Event &e);
        void run();

        //Used to layering stuff that needs be layered on top of each other.
        void pushLayer(Layer *layer);
        void pushOverlay(Layer *layer);
        void popLayer(Layer* layer);
        void popOverlay(Layer* layer);

        //Used for adding stack of game states so it's designed.
        void pushGameLayer(Layer* layer);
        void pushGameOverlay(Layer* layer);
        void popGameLayer(Layer* layer);
        void popGameOverlay(Layer* layer);

        inline static Application& get() { return *_instance; }
        inline Window& getWindow() const { return *_window;  }

        ImGuiLayer* getImGuiLayer();
        float getCurrentLayerZoomLevel() const;

        void close();
    private:
        bool onWindowClosed(WindowClosedEvent &closed);
        bool onWindowResize(WindowResizeEvent& resized);
    private:
        bool _running;
        bool _minimized = false;
        float _zoomLevel = 1.f;
        std::unique_ptr<Window> _window;
        ImGuiLayer* _imGuiLayer;
        //Used for things like ImGuiLayers that need to be on top of every layer.
        LayerStack _layerStack;
        //Used for temprary layers that don't last the duration of the whole application.
        LayerStack _stateStack;

        float _lastFrameTime  = 0.f;
        static Application* _instance;
    };

    //To be defined in the client. This is how you use the shared library.
    Application* createApplication();
}

#endif // TEST_HDR
