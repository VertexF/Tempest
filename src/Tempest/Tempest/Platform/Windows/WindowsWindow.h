#ifndef WINDOWS_WINDOW_HDR
#define WINDOWS_WINDOW_HDR

#include "PreComp.h"

#include <GLFW/glfw3.h>

#include "../../Window.h"

namespace Tempest 
{
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

        struct WindowData 
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            bool vSync;

            EventCallbackFunc eventCallback;
        };

        WindowData _windowData;
    };
}

#endif // WINDOWS_WINDOW_HDR
