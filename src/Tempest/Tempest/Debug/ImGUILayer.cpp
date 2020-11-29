#include "ImGUILayer.h"

#include "PreComp.h"
#include "imgui.h"
#include "../Platform/OpenGL/imgui_impl_opengl3.h"

#include "../Application.h"

#define GLEW_STATIC 1
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Tempest 
{
    ImGuiLayer::ImGuiLayer() : 
        Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach()
    {
    }

    void ImGuiLayer::onUpdate() 
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        float time = static_cast<float>(glfwGetTime());

        io.DeltaTime = _time > 0.f ? (time - _time) : (1.f / 60.f);
        _time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseButtonEventPressed>(std::bind(&ImGuiLayer::onMouseButtonPressedEvent, this, std::placeholders::_1));
        dispatcher.dispatch<MouseButtonEventReleased>(std::bind(&ImGuiLayer::onMouseButtonReleaseEvent, this, std::placeholders::_1));
        dispatcher.dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::onMouseMovedEvent, this, std::placeholders::_1));
        dispatcher.dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::onMouseScrollEvent, this, std::placeholders::_1));
        dispatcher.dispatch<PressedKeyEvent>(std::bind(&ImGuiLayer::onKeyPressedEvent, this, std::placeholders::_1));
        dispatcher.dispatch<ReleasedKeyEvent>(std::bind(&ImGuiLayer::onKeyReleasedEvent, this, std::placeholders::_1));
        dispatcher.dispatch<TypedKeyEvent>(std::bind(&ImGuiLayer::onKeyTypedEvent, this, std::placeholders::_1));
        dispatcher.dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::onWindowResizeEvent, this, std::placeholders::_1));
    }

    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonEventPressed& pressEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[pressEvent.getMouseEvent()] = true;

        return false;
    }

    bool ImGuiLayer::onMouseButtonReleaseEvent(MouseButtonEventReleased& releaseEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[releaseEvent.getMouseEvent()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& mouseMoved)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(mouseMoved.x, mouseMoved.y);

        return false;
    }

    bool ImGuiLayer::onMouseScrollEvent(MouseScrolledEvent& mouseScrolled)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += mouseScrolled.y;
        io.MouseWheelH += mouseScrolled.x;

        return false;
    }

    bool ImGuiLayer::onKeyPressedEvent(PressedKeyEvent& keyPressed)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[keyPressed.getKeyCode()] = true;
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(ReleasedKeyEvent& keyReleased)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[keyReleased.getKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(TypedKeyEvent& keyTyped)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = keyTyped.getKeyCode();

        if (keycode > 0 && keycode < 0x100000)
        {
            io.AddInputCharacter(static_cast<unsigned short>(keycode));
        }

        return false;
    }

    bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent& windowResized)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(windowResized.getWidth(), windowResized.getHeight());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0, 0, windowResized.getWidth(), windowResized.getHeight());

        return false;
    }
}