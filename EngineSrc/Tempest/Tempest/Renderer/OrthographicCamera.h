#ifndef ORTHOGRAPHIC_CAMERA_HDR
#define ORTHOGRAPHIC_CAMERA_HDR

#include <glm/glm.hpp>

namespace Tempest
{
    class OrthographicCamera 
    {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);

        inline const glm::vec3& getPosition() const { return _position; }
        inline float getRotation() const { return _rotation; }
        inline void setPosition(const glm::vec3& position) { _position = position;  recalculateViewMatrix(); }
        inline void setRotation(float rotation) { _rotation = rotation; recalculateViewMatrix(); }

        void setProjection(float left, float right, float top, float bottom);

        inline const glm::mat4x4& getProjectionMatrix() { return _projectionMatrix; }
        inline const glm::mat4x4& getViewMatrix() { return _viewMatrix; }
        inline const glm::mat4x4& getViewProjectionMatrix() { return _viewProjectionMatrix; }
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
