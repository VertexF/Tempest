#include "PreComp.h"
#include "OrthoCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

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
        if (Input::isKeyPressed(TEMP_KEY_W))
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
        }

        _camera.setPosition(_cameraPosition);
        _cameraMovementSpeed = _zoomLevel;
    }

    void OrthographicalCameraController::onEvent(Event& e) 
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(std::bind(&OrthographicalCameraController::onMouseScrolled, this, std::placeholders::_1));
        dispatcher.dispatch<WindowResizeEvent>(std::bind(&OrthographicalCameraController::onWindowResized, this, std::placeholders::_1));
        //dispatcher.dispatch<MouseButtonEventPressed>(std::bind(&OrthographicalCameraController::onMouseTest, this, std::placeholders::_1));
    }

    bool OrthographicalCameraController::onMouseScrolled(MouseScrolledEvent& e) 
    {
        _zoomLevel -= e.y * 0.25f;
        _zoomLevel = std::max(_zoomLevel, 0.25f);
        _camera.setProjection(-_aspectRation * _zoomLevel, _aspectRation * _zoomLevel, -_zoomLevel, _zoomLevel);
        return false;
    }

    bool OrthographicalCameraController::onWindowResized(WindowResizeEvent& e) 
    {
        _aspectRation = (float)e.getWidth() / (float)e.getHeight();
        _camera.setProjection(-_aspectRation * _zoomLevel, _aspectRation * _zoomLevel, -_zoomLevel, _zoomLevel);
        return false;
    }

    bool OrthographicalCameraController::onMouseTest(MouseButtonEventPressed& e)
    {
        TEMPEST_INFO("{0}", e.getMouseEvent());
        return false;
    }
}