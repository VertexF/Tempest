#ifndef WINDOWS_WINDOW_HDR
#define WINDOWS_WINDOW_HDR

#include "PreComp.h"

//Needed to make the GLEW linking is linking to the static version.
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Window.h"

namespace Tempest 
{
    //This is the Windows OS windo versoin.
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps &props);
        virtual ~WindowsWindow();

        virtual void onUpdate() override;

        inline unsigned int getWidth() const override { return _windowData.width; }
        inline unsigned int getHeight() const override { return _windowData.height; }

        //Window attributes.
        inline void setCallbackFunction(const EventCallbackFunc& callback) override { _windowData.eventCallback = callback; }
        virtual void setVSync(bool vsync) override;
        virtual bool isVSync() const override;
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();
    private:
        GLFWwindow *_window;

        //This structure allow use to pass in the window data to GLFW
        //without the need to pass in the WindowsWindow class meaning we can
        //cut down on how much data is being handled by GLFW internally.
        struct WindowData 
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            bool vSync;

            //This allows use to use function callback to events.
            EventCallbackFunc eventCallback;
        };

        WindowData _windowData;
    };
}

#endif // WINDOWS_WINDOW_HDR
