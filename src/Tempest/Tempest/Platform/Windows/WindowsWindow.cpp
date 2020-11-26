#include "WindowsWindow.h"

#include "PreComp.h"

namespace
{
    bool GLFWIntialised = false;
}

namespace Tempest
{
    Window* Window::create(const WindowProps& props) { return new WindowsWindow(props); }

    WindowsWindow::WindowsWindow(const WindowProps& props) {}
    WindowsWindow::~WindowsWindow() {}

    void WindowsWindow::onUpdate() {}

    //Window attributes.
    void WindowsWindow::setVSync() {}
    bool WindowsWindow::isVSync() const { return false; }

    void WindowsWindow::init(const WindowProps& props) {}
    void WindowsWindow::shutdown() {}
}