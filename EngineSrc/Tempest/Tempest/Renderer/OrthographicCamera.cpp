#include "PreComp.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Tempest 
{
    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom) : 
        _projectionMatrix(glm::ortho(left, right, top, bottom, 1.f, -1.f)), _viewMatrix(1.f), _position(0.f, 0.f, 0.f)
    {
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

    void OrthographicCamera::setProjection(float left, float right, float top, float bottom)
    {
        _projectionMatrix = glm::ortho(left, right, top, bottom, 1.f, -1.f);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

    void OrthographicCamera::recalculateViewMatrix()
    {
        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.f), _position) * 
                                glm::rotate(glm::mat4x4(1.f), glm::radians(_rotation), glm::vec3(0, 0, 1));

        _viewMatrix = glm::inverse(transform);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }
}