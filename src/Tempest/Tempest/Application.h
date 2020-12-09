#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include "PreComp.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "LayerStack.h"
#include "Debug/ImGUILayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"

namespace Tempest
{
    class Layer;

    //This is the main coordinator class.
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void onEvent(Event &e);
        void run();

        void pushLayer(Layer *layer);
        void pushOverlay(Layer *layer);

        inline static Application& get() { return *_instance; }
        inline Window& getWindow() const { return *_window;  }
    private:
        bool onWindowClosed(WindowClosedEvent &closed);

        bool _running;
        ImGuiLayer* _imGuiLayer;
        std::unique_ptr<Window> _window;
        LayerStack _layerStack;

        static Application* _instance;

        //OpenGL stuff
        //unsigned int _vertexArray;
        std::shared_ptr<Shader> _shader;
        std::shared_ptr<Shader> _squareShader;

        std::shared_ptr<VertexArray> _vertexArray;
        std::shared_ptr<VertexArray> _squareVA;

        OrthographicCamera _camera;
    };

    //To be defined in the client. This is how you use the shared library.
    Application* createApplication();
}

#endif // TEST_HDR
