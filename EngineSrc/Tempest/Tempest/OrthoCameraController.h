#ifndef ORTHO_CAMERA_CONTROLLER_HDR
#define ORTHO_CAMERA_CONTROLLER_HDR

#include "Renderer/OrthographicCamera.h"
#include "Core/TimeStep.h"

#include "Events/ApplicationEvents.h"
#include "Events/MouseEvents.h"

#include <glm/glm.hpp>

namespace Tempest 
{
    class OrthographicalCameraController 
    {
    public:
        OrthographicalCameraController(float apsectRatio, bool rotation = false);

        void onUpdate(TimeStep ts);
        void onEvent(Event& e);

        OrthographicCamera& getCamera() { return _camera; }
        const OrthographicCamera& getCamera() const { return _camera; }
    private:
        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);
        bool onMouseTest(MouseButtonEventPressed& e);
    private:
        float _aspectRation;
        float _zoomLevel = 1.f;
        //Needs to be below other values
        OrthographicCamera _camera;

        bool _isRotatable;

        float _rotation = 0.f;
        float _rotationSpeed = 10.f;

        float _cameraMovementSpeed = 2.f;
        glm::vec3 _cameraPosition;
    };
}

#endif // !ORTHO_CAMERA_CONTROLLER_HDR
