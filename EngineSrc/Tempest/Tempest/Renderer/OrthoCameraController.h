#ifndef ORTHO_CAMERA_CONTROLLER_HDR
#define ORTHO_CAMERA_CONTROLLER_HDR

#include "OrthographicCamera.h"
#include "Tempest/Core/TimeStep.h"

#include "Tempest/Events/ApplicationEvents.h"
#include "Tempest/Events/MouseEvents.h"

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

        void setZoomLevel(float level) { _zoomLevel = level; calculateView(); }
        float getZoomLevel() const { return _zoomLevel; }

        //TODO: Decouple this class from the application. The player postion
        //should NOT be tied to the camera.
        glm::vec3 getCameraPosition() const { return _cameraPosition; }
        void setCameraPosition(const glm::vec3& position) { _cameraPosition = position; }
    private:
        void calculateView();

        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);
    private:
        float _aspectRation;
        float _zoomLevel = 1.0f;
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
