#ifndef ORTHOGRAPHIC_CAMERA_HDR
#define ORTHOGRAPHIC_CAMERA_HDR

#include <glm/glm.hpp>

namespace Tempest
{
    class OrthographicCamera 
    {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);

        const glm::vec3& getPosition() const { return _position; }
        float getRotation() const { return _rotation; }
        void setPosition(const glm::vec3& position) { _position = position;  recalculateViewMatrix(); }
        void setRotation(float rotation) { _rotation = rotation; recalculateViewMatrix(); }

        void setProjection(float left, float right, float top, float bottom);

        const glm::mat4x4& getProjectionMatrix() const { return _projectionMatrix; }
        const glm::mat4x4& getViewMatrix() const { return _viewMatrix; }
        const glm::mat4x4& getViewProjectionMatrix() const { return _viewProjectionMatrix; }
    private:
        void recalculateViewMatrix();
    private:
        glm::mat4x4 _projectionMatrix;
        glm::mat4x4 _viewMatrix;
        glm::mat4x4 _viewProjectionMatrix;

        glm::vec3 _position;
        float _rotation = 0.f;
    };
}

#endif // !ORTHOGRAPHIC_CAMERA_HDR
