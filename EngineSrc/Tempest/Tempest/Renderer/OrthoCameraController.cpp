#include "PreComp.h"
#include "OrthoCameraController.h"

#include "Tempest/Core/Input.h"
#include "Tempest/Core/KeyCodes.h"
#include "Tempest/Core/TimeStep.h"

namespace Tempest 
{
    OrthographicalCameraController::OrthographicalCameraController(float apsectRatio, bool rotation) :
        _aspectRatio(apsectRatio),
        _camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel),
        _isRotatable(rotation),
        _cameraPosition(0.f)
    {
    }

    void OrthographicalCameraController::onUpdate(TimeStep ts) 
    {
        TEMPEST_PROFILE_FUNCTION();

        ////Rotation
        //if (Input::isKeyPressed(TEMP_KEY_Z))
        //{
        //    _rotation += _rotationSpeed * ts;
        //}
        //else if (Input::isKeyPressed(TEMP_KEY_X))
        //{
        //    _rotation -= _rotationSpeed * ts;
        //}

        _camera.setRotation(_rotation);
        _camera.setPosition(_cameraPosition);
        _cameraMovementSpeed = _zoomLevel;
    }

    void OrthographicalCameraController::autoScroll(TimeStep ts)
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraPosition.x += ts;
    }

    void OrthographicalCameraController::onEvent(Event& e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(std::bind(&OrthographicalCameraController::onMouseScrolled, this, std::placeholders::_1));
        dispatcher.dispatch<WindowResizeEvent>(std::bind(&OrthographicalCameraController::onWindowResized, this, std::placeholders::_1));
    }

    void OrthographicalCameraController::onResize(float width, float height)
    {
        if (height != 0.f)
        {
            _aspectRatio = width / height;
            calculateView();
        }
    }

    void OrthographicalCameraController::calculateView() 
    {
        _camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
    }

    bool OrthographicalCameraController::onMouseScrolled(MouseScrolledEvent& e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        //_zoomLevel -= e.y * 0.25f;
        //_zoomLevel = std::max(_zoomLevel, 0.25f);
        //calculateView();
        return false;
    }

    bool OrthographicalCameraController::onWindowResized(WindowResizeEvent& e) 
    {
        TEMPEST_PROFILE_FUNCTION();
        onResize(static_cast<float>(e.getWidth()), static_cast<float>(e.getHeight()));
        return false;
    }
}