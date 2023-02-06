#ifndef WINDOWS_WINDOW_HDR
#define WINDOWS_WINDOW_HDR

#include "PreComp.h"

//Needed to make the GLEW linking is linking to the static version.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Tempest/Core/Window.h"

namespace Tempest 
{
    class GraphicsContext;

    //This is the Windows OS windo versoin.
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps &props);
        virtual ~WindowsWindow();

        virtual void onUpdate() override;

        uint32_t getWidth() const override;
        uint32_t getHeight() const override;

        //Window attributes.
        void setCallbackFunction(const EventCallbackFunc& callback) override;
        virtual void setVSync(bool vsync) override;
        virtual bool isVSync() const override;

        virtual void* getNativeWindow() const override;
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();
    private:
        GLFWwindow *_window;
        GraphicsContext *_context;

        //This structure allow use to pass in the window data to GLFW
        //without the need to pass in the WindowsWindow class meaning we can
        //cut down on how much data is being handled by GLFW internally.
        struct WindowData 
        {
            std::string title;
            uint32_t width;
            uint32_t height;
            bool vSync;

            //This allows use to use function callback to events.
            EventCallbackFunc eventCallback;
        };

        WindowData _windowData;
    };
}

#endif // WINDOWS_WINDOW_HDR
