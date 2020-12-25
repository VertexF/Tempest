#include "PreComp.h"
#include "OrthoCameraController.h"

#include "Tempest/Core/Input.h"
#include "Tempest/Core/KeyCodes.h"
#include "Tempest/Core/TimeStep.h"

namespace Tempest 
{
    OrthographicalCameraController::OrthographicalCameraController(float apsectRatio, bool rotation) :
        _aspectRation(apsectRatio),
        _camera(-_aspectRation * _zoomLevel, _aspectRation * _zoomLevel, -_zoomLevel, _zoomLevel),
        _isRotatable(rotation),
        _cameraPosition(0.f)
    {
    }

    void OrthographicalCameraController::onUpdate(TimeStep ts) 
    {
        TEMPEST_PROFILE_FUNCTION();

        /*if (Input::isKeyPressed(TEMP_KEY_W))
        {
            _cameraPosition.y += _cameraMovementSpeed * ts;
        }
        else if (Input::isKeyPressed(TEMP_KEY_S))
        {
            _cameraPosition.y -= _cameraMovementSpeed * ts;
        }

        if (Input::isKeyPressed(TEMP_KEY_A))
        {
            _cameraPosition.x -= _cameraMovementSpeed * ts;
        }
        else if (Input::isKeyPressed(TEMP_KEY_D))
        {
            _cameraPosition.x += _cameraMovementSpeed * ts;
        }

        if (_rotation) 
        {
            if (Input::isKeyPressed(TEMP_KEY_Z))
            {
                _rotation += _rotationSpeed * ts;
            }
            else if (Input::isKeyPressed(TEMP_KEY_X))
            {
                _rotation -= _rotationSpeed * ts;
            }

            _camera.setRotation(_rotation);
        }*/

        _camera.setPosition(_cameraPosition);
        _cameraMovementSpeed = _zoomLevel;
    }

    void OrthographicalCameraController::onEvent(Event& e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        //EventDispatcher dispatcher(e);
        //dispatcher.dispatch<MouseScrolledEvent>(std::bind(&OrthographicalCameraController::onMouseScrolled, this, std::placeholders::_1));
        //dispatcher.dispatch<WindowResizeEvent>(std::bind(&OrthographicalCameraController::onWindowResized, this, std::placeholders::_1));
    }

    bool OrthographicalCameraController::onMouseScrolled(MouseScrolledEvent& e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        _zoomLevel -= e.y * 0.25f;
        _zoomLevel = std::max(_zoomLevel, 0.25f);
        _camera.setProjection(-_aspectRation * _zoomLevel, _aspectRation * _zoomLevel, -_zoomLevel, _zoomLevel);
        return false;
    }

    bool OrthographicalCameraController::onWindowResized(WindowResizeEvent& e) 
    {
        TEMPEST_PROFILE_FUNCTION();

        _aspectRation = (float)e.getWidth() / (float)e.getHeight();
        _camera.setProjection(-_aspectRation * _zoomLevel, _aspectRation * _zoomLevel, -_zoomLevel, _zoomLevel);
        return false;
    }
}